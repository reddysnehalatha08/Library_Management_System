#ifndef INPUT_H
#define INPUT_H

void read_line(char *str, int size);
int read_int(const char *message);
float read_float(const char *message);
void read_non_empty(const char *message, char *str, int size);

#endif
