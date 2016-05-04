#define DEF_HEIGHT 640.0
#define DEF_WIDTH 800.0
#define CONFIG_PATH "res/.config"

#define SINGLEPLAY 0
#define CLIENT 1
#define SERVER 2

class Kernel
{
public:
	Kernel(int argc, char **argv);
    float width;
    float height;
    bool fullscreen;
    int mode;
	char* server_address;
private:
	char* map_name;
	void load_config();
	void save_config();
	void do_command(char* input);
};
