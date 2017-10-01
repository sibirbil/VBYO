# coding=utf-8
from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession

sparkConf = SparkConf().setAppName("Yapay Ogrenme").setMaster("local[*]")
sc = SparkContext(conf = sparkConf)
spark = SparkSession.builder.appName("Yapay Ogrenme SQL").getOrCreate()
sc.setLogLevel("ERROR")

arr = range(10)
rdd = sc.parallelize(arr)


def kareAl(x):
    if(x%2==0):
        return x * x
    else:
        return x


print rdd.map(kareAl).filter(lambda  x : x<10).reduce(lambda x,y:  x+y)



