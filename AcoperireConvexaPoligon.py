import math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def pointPositionDeterminant(P, Q, R):
    det = Q.x*R.y + P.x*Q.y + R.x*P.y - P.x*R.y - Q.x*P.y - R.x*Q.y;
    if det > 0:
        return 1
    elif det < 0:
        return -1
    else:
        return 0

def distance(P, Q):
    return math.sqrt((P.x - Q.x)**2 + (P.y - Q.y)**2)

def leftmostPoint(P):
    min = P[1]
    for i in range(1, len(P)):
        if P[i].x < min.x:
            min = P[i]
    return min

def Jarvis (P):
    on_hull = leftmostPoint(P)
    hull = []
    while True:
        hull.append(on_hull)
        next_point = P[1]
        for i in range(1, len(P)):
            position = pointPositionDeterminant(on_hull, next_point, P[i])
            if position < 0 or (position == 0 and distance(on_hull, P[i]) > distance(on_hull, next_point)):
                next_point = P[i]
        on_hull = next_point
        if next_point == hull[1]:
            break
    return hull

def main():
    P = [Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0), Point(0.5, 0.5)]
    hull = Jarvis(P)
    for i in range(0, len(hull)):
        print(hull[i].x, hull[i].y)

main()