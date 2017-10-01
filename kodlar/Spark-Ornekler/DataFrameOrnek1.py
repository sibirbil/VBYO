# coding=utf-8
from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession

sparkConf = SparkConf().setAppName("Yapay Ogrenme").setMaster("local[*]")
sc = SparkContext(conf = sparkConf)
spark = SparkSession.builder.appName("Yapay Ogrenme SQL").getOrCreate()
sc.setLogLevel("ERROR")


df = spark.read.format("csv").option("header", "true").option("inferSchema", "true").csv("world.csv") 
df.printSchema()
print "--------"
df2 = df.select("Ulke","Nufus").filter("Nufus > 50000000").sort("Nufus",ascending=False)
df3 = df2.withColumn("YeniKolon",(df2["Nufus"]/2))
df3.show()


