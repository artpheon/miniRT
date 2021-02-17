unsigned char	*file_header_bmp(int filesize);
unsigned char	*info_header_bmp(t_resolution resolution);
void			write_data(int f, const unsigned char *data, t_resolution resolution, const int filesize);
void			save_bmp(const char *filename, const unsigned char *data, const t_resolution resolution);
