t_vector set_vector(float x, float y, float z);
void exit_error(char *message, int errn);
t_ray set_ray(t_vector origin, t_vector dir);
t_vector set_nvector(float x, float y, float z);
int ctohex(t_vector rgb);
t_vector hextoc(int hex);
float macheps(void);