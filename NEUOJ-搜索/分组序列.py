n, k = map(int, input().split())
x = list(map(int, input().split()))
max_x = max(x)
sum_x = sum(x)

left = max_x
right = sum_x

def is_possible(mid):
    if mid < max_x:
        return False
    count = 1
    current_sum = 0
    for num in x:
        if current_sum + num > mid:
            count += 1
            current_sum = num
            if count > k:
                return False
        else:
            current_sum += num
    return True

while left < right:
    mid = (left + right) // 2
    if is_possible(mid):
        right = mid
    else:
        left = mid + 1

print(left)