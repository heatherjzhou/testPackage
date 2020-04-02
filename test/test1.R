#devtools::install_github("heatherjzhou/testPackage")
library(testPackage)

set.seed(1)
res1<-testFunction(m=7,n=3)
print(res1)
set.seed(1)
res2<-testFunction(m=7,n=3)
print(res2)
print(res1==res2)

#Not declaring seed or rng as constants gives the following results:
# [,1]       [,2]       [,3]
# [1,] 2.984820 -0.2167465  5.6327765
# [2,] 2.503436  2.9743294  2.0956222
# [3,] 2.376704  1.8565628  4.7034563
# [4,] 3.760149  2.5614912 -0.2492637
# [5,] 1.285446  2.2520530  4.8168816
# [6,] 2.193879  0.6136235  0.1582772
# [7,] 5.004521  2.3059983  1.6349219

set.seed(7)
res1<-testFunction(m=7,n=3)
print(res1)
set.seed(7)
res2<-testFunction(m=7,n=3)
print(res2)
print(res1==res2)

# [,1]       [,2]       [,3]
# [1,] 0.3331488  0.5412220  6.0030053
# [2,] 1.2583198  3.3286762 -0.2057502
# [3,] 3.4155020  2.3096985  4.4715244
# [4,] 3.8112075  1.6871061  2.1248432
# [5,] 4.6677981  2.1305524  3.4101351
# [6,] 4.6677089 -0.2866022  2.7095798
# [7,] 3.4638918  1.0408845  2.6689925
