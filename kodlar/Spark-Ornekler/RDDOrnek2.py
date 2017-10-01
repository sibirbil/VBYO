# coding=utf-8
from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession

sparkConf = SparkConf().setAppName("Yapay Ogrenme").setMaster("local[*]")
sc = SparkContext(conf = sparkConf)
spark = SparkSession.builder.appName("Yapay Ogrenme SQL").getOrCreate()
sc.setLogLevel("ERROR")

worldRDD = sc.textFile("world.txt")
#print worldRDD.collect()


def processLine(line):
    arr = line.split(",")
    return long(arr[3])

# Asya kıtasında yaşayan insan sayısı
print worldRDD.filter(lambda  line: "Asia" in line).map(processLine).reduce(lambda x,y:x+y)

