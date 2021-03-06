/*
 * 문제를 나이브하게 푸는 방법은 가능한 모든 조합을 일일히 검사해서 k로 나눠떨어지는지 살피고,
 * 만약 두 번 이상 포함되었다면 제거하는 방법일 것이다. 
 * 
 * 하지만 문제를 푸는 더 나은 방법도 있다.
 * 
 * Biggest non-divisible sets [출처: https://www.geeksforgeeks.org/subset-no-pair-sum-divisible-k/]
 * 이 문제 또한 문제를 단순하게 만들기 위해 remainder를 사용하는데(sherlock and squares와 비슷한 케이스),
 * remainder를 사용하면 문제가 훨씬 극적으로 단순해진다.
 * 
 * 정수의 성질 중 하나인 a + b % k == 0 이면 a % k + b % k == k
 * 이 성질을 이용하면 
 * 나머지 i와 나머지 k - i 중 더 많은 쪽을 계속해서 집합에 집어넣다보면 가장 큰 non divisible set이 됨을 알 수 있다.
 * 
 * 예시) {1, 7, 2, 4} k = 3
 * 나머지들: 1 1 2 1
 * 
 * 여기서보면 나머지가 1인 두 수는 아무리 더해도 3으로 나눠지지 않고 오직 나머지가 2인 수와 나머지가 1인 수를 더해야만 3으로 나눠지는 것을 확인할 수 있다.
 * 그러므로 나머지가 i인 경우와 나머지가 k - i인 경우는 서로 배타적인 경우가 된다. 
 * 문제에서는 가장 큰 크기의 non divisible set을 구하므로 두 경우 중 더 큰 경우를 택하게 된다.
 * 
 * 살펴봐야할 edge case로는 나머지가 0인 경우와 나머지가 k / 2인 경우를 들 수 있는데,
 * 나머지가 0이면 또 다른 나머지가 0인 수와 합했을 때 나눠떨어지게 된다.
 * 그러나 나머지가 0이 아닌 숫자와는 아무리 합해도 나눠떨어지지 않는데 (0 + 1 or 0 + 2를 해봐도 3은 될 수 없음),
 * 이를 생각해보면 나머지가 0인 숫자는 최대 1번까지 포함됨을 알 수 있다.
 * 
 * 나머지가 k / 2인 경우도 나머지가 0인 경우와 마찬가지다.
 */
int nonDivisibleSubset(int k, vector<int> S)
{
  // 가능한 나머지의 갯수만큼 배열 설정
  int f[k];

  // 메모리를 일괄적으로 어떤 값으로 설정
  memset(f, 0, sizeof(f));

  for (auto s : S)
    f[s % k]++;

  // k가 짝수인 경우 k/2인 나머지는 최대 1번 선택된다.
  if (k % 2 == 0)
    f[k / 2] = min(f[k / 2], 1);

  // 마찬가지로 나머지가 0인 경우 최대 1번 선택됨
  int answer = min(f[0], 1);

  // 이제 k/2까지 반복문을 돌리는데 이 이유는
  // i, k - i의 조합을 배타적으로 선택하려면 k / 2까지만 선택해야되기 때문
  // ex) k = 5
  // 1 - 4
  // 2 - 3 // k / 2인 구간 - 여기까지만 해야 중복을 막을 수 있다.
  // 3 - 2
  // 4 - 1
  for (int i = 1; i <= k / 2; i++)
    answer += max(f[i], f[k - i]);

  return answer;
}
