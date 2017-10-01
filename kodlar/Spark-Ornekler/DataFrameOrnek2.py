# coding=utf-8
from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.regression import LinearRegression, RandomForestRegressor

sparkConf = SparkConf().setAppName("Yapay Ogrenme").setMaster("local[*]")
sc = SparkContext(conf = sparkConf)
spark = SparkSession.builder.appName("Yapay Ogrenme SQL").getOrCreate()
sc.setLogLevel("ERROR")


df = spark.read.format("csv").option("header", "true").option("inferSchema", "true").csv("realestate.csv") 
df.printSchema()
print "--------"


df = df.na.fill(0,df.columns[1:])

dfR = df.drop("transactiondate").withColumnRenamed("logerror","label")


vecAssembler = VectorAssembler(inputCols=dfR.columns[1:-1], outputCol="features")
dfWithFeatures =  vecAssembler.transform(dfR)


(trainingData, testData)  = dfWithFeatures.randomSplit([0.7, 0.3])

trainingData.show()




lr = RandomForestRegressor(featuresCol="features", labelCol="label", predictionCol="prediction")
model = lr.fit(trainingData)

predictionsDF = model.transform(testData)

predictionsDF.drop("features").write.option("header", "true").csv("test.csv")



