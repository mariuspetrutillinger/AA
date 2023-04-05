n = int(input())
left_limits = []
right_limits = []
down_limits = []
up_limits = []

for i in range(n):
    less_than = True
    a, b, c = map(int, input().split())
    if a == 0:
        if b < 0:
            less_than = False
        limit = -c / b
        if less_than:
            up_limits.append(limit)
        else:
            down_limits.append(limit)
    else:
        if a < 0:
            less_than = False
        limit = -c / a
        if less_than:
            right_limits.append(limit)
        else:
            left_limits.append(limit)

m = int(input())
left_limits.sort()
right_limits.sort()
down_limits.sort()
up_limits.sort()

for i in range(m):
    x, y = map(float, input().split())

    left_index = right_limits_index = down_index = up_index = -1
    for j, limit in enumerate(left_limits):
        if limit < x:
            left_index = j
        else:
            break

    for j, limit in enumerate(right_limits):
        if limit > x:
            right_index = j
            break

    for j, limit in enumerate(down_limits):
        if limit < y:
            down_index = j
        else:
            break

    for j, limit in enumerate(up_limits):
        if limit > y:
            up_index = j
            break

    if left_index == -1 or right_index == -1 or down_index == -1 or up_index == -1:
        print("NO")
    else:
        area = (right_limits[right_index] - left_limits[left_index]) * (up_limits[up_index] - down_limits[down_index])
        print("YES")
        print("{:.6f}".format(area))
