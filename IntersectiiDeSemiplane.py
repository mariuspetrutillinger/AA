# Take input for number of inequalities to be checked
n = int(input())

# Initialize the boundary coordinates of the feasible region
xLeft = yDown = xMin - 5
xRight = yUp = xMax + 5

# Loop through the inequalities
for i in range(n):
    # Take input for the coefficients of the inequality
    a, b, c = map(int, input().split())

    # Check if the inequality is in the form of "by + c <= 0"
    if a == 0:
        # Determine the limit for the boundary coordinate
        limit = (double)(-c) / b

        # Update the boundary coordinates based on the inequality
        if b < 0:
            yUp = min(yUp, limit)
        else:
            yDown = max(yDown, limit)
    else: 
        # The inequality is in the form of "ax + c <= 0"
        # Determine the limit for the boundary coordinate
        limit = (double)(-c) / a

        # Update the boundary coordinates based on the inequality
        if a < 0:
            xRight = min(xRight, limit)
        else:
            xLeft = max(xLeft, limit)

# Check if the feasible region is bounded, unbounded or void and print the output
if xLeft > xRight or yDown > yUp:
    print("VOID")
elif xLeft == xMin - 5 or yDown == xMin - 5 or xRight == xMax + 5 or yUp == xMax + 5:
    print("UNBOUNDED")
else:
    print("BOUNDED")
