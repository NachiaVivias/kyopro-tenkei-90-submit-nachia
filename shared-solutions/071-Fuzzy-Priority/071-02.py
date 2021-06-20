N,M,K = map(int,input().split())
E = [[] for i in range(N)]
inIdx = [0] * N
for i in range(M):
  a,b = map(int,input().split())
  a -= 1
  b -= 1
  E[a].append(b)
  inIdx[b] += 1

topological_que = []
recursive_stack = []
for i in range(N):
  if inIdx[i] == 0:
    topological_que += [i]
recursive_stack.append([0,len(topological_que)])
topological_que += [0] * (N - len(topological_que))

ans = []
while len(recursive_stack) != 0:
  i = len(recursive_stack) - 1
  st = recursive_stack[-1]
  if i == N:
    ans.append([x for x in topological_que])
    recursive_stack.pop()
    if len(recursive_stack) != 0:
      prei = i-1
      pres = recursive_stack[-1]
      for e in E[topological_que[prei]]: inIdx[e] += 1
      topological_que[prei],topological_que[pres[0]] = topological_que[pres[0]],topological_que[prei]
      recursive_stack[-1][0] += 1
    continue
  if st[1] == i:
    # no valid answer
    break
  if st[0] >= st[1]:
    recursive_stack.pop()
    if len(recursive_stack) != 0:
      prei = i-1
      pres = recursive_stack[-1]
      for e in E[topological_que[prei]]: inIdx[e] += 1
      topological_que[prei],topological_que[pres[0]] = topological_que[pres[0]],topological_que[prei]
      pres[0] += 1
    continue
  if len(ans) == K:
    break

  pres = recursive_stack[-1]
  que_back = pres[1]
  topological_que[i] , topological_que[pres[0]] = topological_que[pres[0]] , topological_que[i]
  p = topological_que[i]
  for e in E[p]:
    inIdx[e] -= 1
    if inIdx[e] == 0:
      topological_que[que_back] = e
      que_back += 1
  recursive_stack.append([ i+1,que_back ])

if len(ans) != K:
  print(-1)
else:
  print("\n".join([" ".join([str(x+1) for x in a]) for a in ans]))
