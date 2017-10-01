# coding=utf-8
from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession

sparkConf = SparkConf().setAppName("Yapay Ogrenme").setMaster("local[*]")
sc = SparkContext(conf = sparkConf)
spark = SparkSession.builder.appName("Yapay Ogrenme SQL").getOrCreate()
sc.setLogLevel("ERROR")

a = [("ahmet",11,34),("ali",12,34),("veli",13,34)]
b = [("ahmet","Ankara"),("ali","Adana"),("veli","İstanbul")]

aRDD = sc.parallelize(a)
bRDD = sc.parallelize(b)

print aRDD.join(bRDD).collect()
