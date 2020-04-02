devtools::install_github("heatherjzhou/testPackage",auth_token="7b41bc7fba5cd2c0abbc2ca9feb7abc982dd8a8c")
library(testPackage)

set.seed(1)
res1<-testFunction(m=7,n=3)
print(res1)
set.seed(1)
res2<-testFunction(m=7,n=3)
print(res2)
print(res1==res2)

set.seed(7)
res1<-testFunction(m=7,n=3)
print(res1)
set.seed(7)
res2<-testFunction(m=7,n=3)
print(res2)
print(res1==res2)

