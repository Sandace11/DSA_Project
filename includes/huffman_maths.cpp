#include "huffman_maths.h"
#include <cstring>
#include <math.h>

double to_rad(double d) { return (acos(-1) * d) / 180; }

Pair::Pair(double a, double b) {
  x = a;
  y = b;
}

/* Intersection between line and parent circle
 * This will be starting point of arrow
 */

/* Returns +1 or -1 depending upon root */
double get_sign(const char *from, const char *child_name) {
  double sign;
  if (((strcmp("parent", from) == 0) && (strcmp(child_name, "left") == 0)) or
      ((strcmp("child", from) == 0) && (strcmp(child_name, "right") == 0)))
    sign = -1;
  else
    sign = 1;

  return sign;
}

Pair parent_line_intersection(double p_x, double p_y, double c_x, double c_y,
                              double r, const char *child_name) {
  double m = (c_y - p_y) / (c_x - p_x);

  double sign = get_sign("parent", child_name);

  double x = p_x + sign * r / sqrt(pow(m, 2) + 1);
  double y = m * (x - p_x) + p_y;

  return Pair(x, y);
}

Pair child_line_intersection(double p_x, double p_y, double c_x, double c_y,
                             double r, const char *child_name) {
  double m = (c_y - p_y) / (c_x - p_x);

  double sign = get_sign("child", child_name);

  double x = c_x + sign * (r / sqrt(pow(m, 2) + 1));

  double y = m * (x - c_x) + c_y;

  return Pair(x, y);
}
