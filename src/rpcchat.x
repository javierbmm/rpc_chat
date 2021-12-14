enum status{ ERROR=0, OK=1 };

program  rpcchat {
    version rpcchat_version {
        status write(string) = 1;
        string getChat(void) = 2;
    } = 0;
} = 0x20000001;