def generate_endpoints(slope, lines, filename):
    x0 = 0
    x1 = 1000
    y_start = 0
    y_adjust = 20
    with open(filename, 'a+') as f:
        for i in range(lines):
            by0 = y_start + i * y_adjust
            by1 = by0 + int(slope * (x1 - x0))

            wy0 = y_start + i * y_adjust + 10
            wy1 = wy0 + int(slope * (x1 - x0))

            f.write(f"{x0} {by0} {x1} {by1} {x0} {wy0} {x1} {wy1}\n")

def generate_steep_endpoints(slope, lines, filename):
    y0 = 0
    y1 = 1000
    x_start = 0
    x_adjust = 20
    with open(filename, 'a+') as f:
        for i in range(lines):
            bx0 = x_start + i * x_adjust
            bx1 = bx0 + int((y1 - y0) / slope)

            wx0 = x_start + i * x_adjust + 10
            wx1 = wx0 + int((y1 - y0) / slope)

            f.write(f"{bx0} {y0} {bx1} {y1} {wx0} {y0} {wx1} {y1}\n")

def generate_vertical_endpoints(lines, filename):
    y0 = 0
    y1 = 1000
    x_start = 0
    x_adjust = 20
    with open(filename, 'a+') as f:
        for i in range(lines):
            bx0 = x_start + i * x_adjust
            bx1 = bx0

            wx0 = x_start + i * x_adjust + 10
            wx1 = wx0

            f.write(f"{bx0} {y0} {bx1} {y1} {wx0} {y0} {wx1} {y1}\n")

generate_endpoints(0.1, 200, "positive.in")
generate_endpoints(0.25, 200, "positive.in")
generate_endpoints(0.5, 200, "positive.in")
generate_endpoints(0.75, 200, "positive.in")
generate_endpoints(1, 200, "positive.in")

generate_endpoints(-0.1, 200, "negative.in")
generate_endpoints(-0.25, 200, "negative.in")
generate_endpoints(-0.5, 200, "negative.in")
generate_endpoints(-0.75, 200, "negative.in")
generate_endpoints(-1, 200, "negative.in")

generate_steep_endpoints(1.25, 200, "steep_positive.in")
generate_steep_endpoints(1.5, 200, "steep_positive.in")
generate_steep_endpoints(2, 200, "steep_positive.in")
generate_steep_endpoints(2.5, 200, "steep_positive.in")
generate_steep_endpoints(3, 200, "steep_positive.in")

generate_steep_endpoints(-1.25, 200, "steep_negative.in")
generate_steep_endpoints(-1.5, 200, "steep_negative.in")
generate_steep_endpoints(-2, 200, "steep_negative.in")
generate_steep_endpoints(-2.5, 200, "steep_negative.in")
generate_steep_endpoints(-3, 200, "steep_negative.in")

generate_endpoints(0, 1000, "horizontal.in")
generate_vertical_endpoints(1000, "vertical.in")