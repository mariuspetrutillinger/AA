class Point:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

def determinant(A: Point, B: Point, C: Point, D: Point) -> int:
    x1 = B.x - A.x
    x2 = B.y - A.y
    y1 = C.x - A.x
    y2 = C.y - A.y
    z1 = D.x - A.x
    z2 = D.y - A.y
    x3 = B.x**2 - A.x**2 + B.y**2 - A.y**2
    y3 = C.x**2 - A.x**2 + C.y**2 - A.y**2
    z3 = D.x**2 - A.x**2 + D.y**2 - A.y**2

    s2 = z1*y2*x3 + z2*y3*x1 + x2*y1*z3
    s1 = x1*y2*z3 + y1*z2*x3 + x2*y3*z1

    return s2 - s1

points = []

A = [int(x) for x in input().split(' ')]
B = [int(x) for x in input().split(' ')]
C = [int(x) for x in input().split(' ')]
D = [int(x) for x in input().split(' ')]
A = Point(A[0], A[1])
B = Point(B[0], B[1])
C = Point(C[0], C[1])
D = Point(D[0], D[1])

if (determinant(A, B, C, D)) > 0:
    print ('AC: ILLEGAL')
elif (determinant(A, B, C, D)) <= 0:
    print ('AC: LEGAL')

if (determinant(B, C, D, A)) > 0:
    print ('BD: ILLEGAL')
elif (determinant(B, C, D, A)) <= 0:
    print ('BD: LEGAL')