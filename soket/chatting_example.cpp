#define MAX_SIZE 1024 //상수 선언
#define MAX_CLIENT 3 //최대 인원 3

struct SOCKET_INFO { //// 연결된 소켓 정보에 대한 틀 생성
    SOCKET sck = 0; //ctrl + 클릭, unsigned int pointer형
    string user = ""; //user  : 사람의 이름
};

std::vector<SOCKET_INFO> sck_list; // 연결된 클라이언트 소켓들을 저장할 배열 선언.
SOCKET_INFO server_sock; // 서버 소켓에 대한 정보를 저장할 변수 선언.
int client_count = 0; // 현재 접속해 있는 클라이언트를 count 할 변수 선언.

void server_init() //서버측 소켓 활성화 ,
{
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN server_addr = {};
    // 소켓 주소 설정 변수
    server_addr.sin_family = AF_INET;
    // 소켓은 Internet 타입 
    server_addr.sin_port = htons(7777); //123.0.0.1:7777 중에 ------:7777을 정의
    // 서버 포트 설정
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //123.0.0.1:----을 정의한다.
    // Any인 경우는 호스트를 127.0.0.1로 잡아도 되고 localhost로 잡아도 되고 양쪽 다 허용하게 할 수 있다. 그것이 INADDR_ANY이다.

    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));
    // 설정된 소켓 정보를 소켓에 바인딩한다.

    listen(server_sock.sck, SOMAXCONN);
    // 소켓을 대기 상태로 기다린다.

    server_sock.user = "server";
}

void add_client() {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };

    ZeroMemory(&addr, addrsize);
    // addr의 메모리 영역을 0으로 초기화

    SOCKET_INFO new_client = {};

    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0);
    // Winsock2의 recv 함수. client가 보낸 닉네임을 받음.
    new_client.user = string(buf);

    string msg = "▶" + new_client.user + " 님이 입장했습니다.";
    cout << msg << endl;
    sck_list.push_back(new_client);
    // client 정보를 담는 sck_list 배열에 새로운 client 추가
    print_clients();

    std::thread th(recv_msg, client_count);
    // 다른 사람들로부터 오는 메시지를 계속해서 받을 수 있는 상태로 만들어 두기
    th.detach();
    client_count++;

    cout << "▷현재 접속자 수 : " << client_count << "명" << endl;
    send_msg(msg.c_str());
    // c_str : string 타입을 const chqr* 타입으로 바꿔줌.
}

void send_msg(const char* msg)
{
    for (int i = 0; i < client_count; i++)
    {
        send(sck_list[i].sck, msg, MAX_SIZE, 0);
        // 접속해 있는 모든 client에게 메시지 전송
    }
}

void send_msg_notMe(const char* msg, int sender_idx)
{
    for (int i = 0; i < client_count; i++) {
        if (i != sender_idx) {
            send(sck_list[i].sck, msg, MAX_SIZE, 0);
        }
    }
}

void sendWhisper(int position, string sbuf, int idx)
{
    int cur_position = position + 1;
    position = sbuf.find(" ", cur_position);
    int len = position - cur_position;
    string receiver = sbuf.substr(cur_position, len);
    cur_position = position + 1;
    string dm = sbuf.substr(cur_position);
    string msg = "※귓속말 도착 [" + sck_list[idx].user + "] : " + dm;
    for (int i = 0; i < client_count; i++)
    {
        if (receiver.compare(sck_list[i].user) == 0)
            send(sck_list[i].sck, msg.c_str(), MAX_SIZE, 0);
    }
}

void recv_msg(int idx)
{
    char buf[MAX_SIZE] = { };
    string msg = "";

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);

        if (recv(sck_list[idx].sck, buf, MAX_SIZE, 0) > 0) {
            // 오류가 발생하지 않으면 recv는 수신된 바이트 수를 반환. 0보다 크다는 것은 메시지가 왔다는 것.
            string whisper(buf);
            int position = whisper.find(" ", 0);
            int message = position - 0;
            string flag = whisper.substr(0, message);
            if (string(buf) == "/종료")
            {
                msg = "▶" + sck_list[idx].user + " 님이 퇴장했습니다.";
                cout << msg << endl;
                send_msg(msg.c_str());
                del_client(idx);
                return;
            }
            else if (flag.compare("/귓말") == 0)
            {
                sendWhisper(position, whisper, idx);
            }
            else {

                pstmt = con->prepareStatement("INSERT INTO chatting(chatname, time, recv) VALUE(?, NOW(),  ?)");
                pstmt->setString(1, sck_list[idx].user);
                pstmt->setString(2, whisper);
                pstmt->execute();

                pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting ORDER BY time DESC LIMIT 1");
                result = pstmt->executeQuery();
                if (result->next())
                {
                    string chatname = result->getString(1);
                    string time = result->getString(2);
                    string recv = result->getString(3);
                    msg += "--------------------------------------------------";
                    msg += "\n▷보낸사람: " + chatname + "  " + "▷보낸시간: " + time + "\n";
                    msg += "▷내용 : " + recv + "\n";
                    msg += "--------------------------------------------------\n";
                    cout << msg << endl;
                    send_msg_notMe(msg.c_str(), idx);
                }
            }
        }
        else { //그렇지 않을 경우 퇴장에 대한 신호로 생각하여 퇴장 메시지 전송
            msg = "[공지] " + sck_list[idx].user + " 님이 퇴장했습니다.";
            cout << msg << endl;
            send_msg(msg.c_str());
            del_client(idx); // 클라이언트 삭제
            return;
        }
    }
}