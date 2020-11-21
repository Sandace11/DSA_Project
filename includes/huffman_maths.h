#ifndef HUFFMAN_MATHS
#define HUFFMAN_MATHS

double to_rad(double d);

class Pair {
public:
  double x;
  double y;

  Pair(double a, double b);
};

double get_sign(const char *from, const char *child_name);
Pair parent_line_intersection(double p_x, double p_y, double c_x, double c_y,
                              double r, const char *child_name);
Pair child_line_intersection(double p_x, double p_y, double c_x, double c_y,
                             double r, const char *child_name);
#endif
