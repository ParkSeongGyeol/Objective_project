#define MAX_SIZE 1024 //��� ����
#define MAX_CLIENT 3 //�ִ� �ο� 3

struct SOCKET_INFO { //// ����� ���� ������ ���� Ʋ ����
    SOCKET sck = 0; //ctrl + Ŭ��, unsigned int pointer��
    string user = ""; //user  : ����� �̸�
};

std::vector<SOCKET_INFO> sck_list; // ����� Ŭ���̾�Ʈ ���ϵ��� ������ �迭 ����.
SOCKET_INFO server_sock; // ���� ���Ͽ� ���� ������ ������ ���� ����.
int client_count = 0; // ���� ������ �ִ� Ŭ���̾�Ʈ�� count �� ���� ����.

void server_init() //������ ���� Ȱ��ȭ ,
{
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN server_addr = {};
    // ���� �ּ� ���� ����
    server_addr.sin_family = AF_INET;
    // ������ Internet Ÿ�� 
    server_addr.sin_port = htons(7777); //123.0.0.1:7777 �߿� ------:7777�� ����
    // ���� ��Ʈ ����
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //123.0.0.1:----�� �����Ѵ�.
    // Any�� ���� ȣ��Ʈ�� 127.0.0.1�� ��Ƶ� �ǰ� localhost�� ��Ƶ� �ǰ� ���� �� ����ϰ� �� �� �ִ�. �װ��� INADDR_ANY�̴�.

    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));
    // ������ ���� ������ ���Ͽ� ���ε��Ѵ�.

    listen(server_sock.sck, SOMAXCONN);
    // ������ ��� ���·� ��ٸ���.

    server_sock.user = "server";
}

void add_client() {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };

    ZeroMemory(&addr, addrsize);
    // addr�� �޸� ������ 0���� �ʱ�ȭ

    SOCKET_INFO new_client = {};

    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0);
    // Winsock2�� recv �Լ�. client�� ���� �г����� ����.
    new_client.user = string(buf);

    string msg = "��" + new_client.user + " ���� �����߽��ϴ�.";
    cout << msg << endl;
    sck_list.push_back(new_client);
    // client ������ ��� sck_list �迭�� ���ο� client �߰�
    print_clients();

    std::thread th(recv_msg, client_count);
    // �ٸ� �����κ��� ���� �޽����� ����ؼ� ���� �� �ִ� ���·� ����� �α�
    th.detach();
    client_count++;

    cout << "������ ������ �� : " << client_count << "��" << endl;
    send_msg(msg.c_str());
    // c_str : string Ÿ���� const chqr* Ÿ������ �ٲ���.
}

void send_msg(const char* msg)
{
    for (int i = 0; i < client_count; i++)
    {
        send(sck_list[i].sck, msg, MAX_SIZE, 0);
        // ������ �ִ� ��� client���� �޽��� ����
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
    string msg = "�رӼӸ� ���� [" + sck_list[idx].user + "] : " + dm;
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
            // ������ �߻����� ������ recv�� ���ŵ� ����Ʈ ���� ��ȯ. 0���� ũ�ٴ� ���� �޽����� �Դٴ� ��.
            string whisper(buf);
            int position = whisper.find(" ", 0);
            int message = position - 0;
            string flag = whisper.substr(0, message);
            if (string(buf) == "/����")
            {
                msg = "��" + sck_list[idx].user + " ���� �����߽��ϴ�.";
                cout << msg << endl;
                send_msg(msg.c_str());
                del_client(idx);
                return;
            }
            else if (flag.compare("/�Ӹ�") == 0)
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
                    msg += "\n���������: " + chatname + "  " + "�������ð�: " + time + "\n";
                    msg += "������ : " + recv + "\n";
                    msg += "--------------------------------------------------\n";
                    cout << msg << endl;
                    send_msg_notMe(msg.c_str(), idx);
                }
            }
        }
        else { //�׷��� ���� ��� ���忡 ���� ��ȣ�� �����Ͽ� ���� �޽��� ����
            msg = "[����] " + sck_list[idx].user + " ���� �����߽��ϴ�.";
            cout << msg << endl;
            send_msg(msg.c_str());
            del_client(idx); // Ŭ���̾�Ʈ ����
            return;
        }
    }
}