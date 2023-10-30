class point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def intersects(p1: point, p2: point, p3: point, p4: point) -> point:
    s1 = point(p2.x - p1.x, p2.y - p1.y)
    s2 = point(p4.x - p3.x, p4.y - p3.y)

    s = (-s1.y * (p1.x - p3.x) + s1.x * (p1.y - p3.y)) / (-s2.x * s1.y + s1.x * s2.y)
    t = ( s2.x * (p1.y - p3.y) - s2.y * (p1.x - p3.x)) / (-s2.x * s1.y + s1.x * s2.y)

    if (s >= 0 and s <= 1 and t >= 0 and t <= 1):
        return point( p1.x + (t * s1.x),
                      p1.y + (t * s1.y) )

p1 = point(1, 3)
p2 = point(4, 3)
p3 = point(3, 2)
p4 = point(3, 5)

i = intersects(p1, p2, p3, p4)

print(str(i.x) + ", " + str(i.y))
