library(testPackage)

res1<-testFunction(m=7,n=3,seed=5)
print(res1)
res2<-testFunction(m=7,n=3,seed=5)
print(res2)
print(res1==res2)

res1<-testFunction(m=7,n=3,seed=5)
res1<-testFunction(m=7,n=3,seed=NULL)
