class Kernel
{
public:
	Kernel(int argc, char **argv);
private:
	char* map_name;
	static constexpr char *optString = "m";

};
