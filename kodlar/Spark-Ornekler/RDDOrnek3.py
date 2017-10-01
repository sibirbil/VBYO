# coding=utf-8
from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession

sparkConf = SparkConf().setAppName("Yapay Ogrenme").setMaster("local[*]")
sc = SparkContext(conf = sparkConf)
spark = SparkSession.builder.appName("Yapay Ogrenme SQL").getOrCreate()
sc.setLogLevel("ERROR")

worldRDD = sc.textFile("world.txt")



def processLine(line):
    arr = line.split(",")
    return [arr[1],long(arr[3])]

def toplamNufus(kita):
    total = 0;
    for nufus in kita[1]:
        total = total + nufus
    return (kita[0],total)
        

# Asya kıtasında yaşayan insan sayısı
sonuc = worldRDD.map(processLine).groupByKey().map(toplamNufus).collect()
for s in sonuc:
    print s[0] + " : "+str(s[1])

