# -*- coding: utf-8 -*-
import numpy as np
from matplotlib import pyplot as plt

#定义线性回归的函数，返回最终训练生成的系数，这里alpha是学习速率，iters是迭代次数
def linearRegression(alpha = 0.01, iters = 1000):
    print("加载数据...\n")
    #读取需要训练的数据集
    data = np.loadtxt('data1.txt', delimiter=',', dtype=np.float64)
    X = data[:, 0:-1] #X保存数据集的第一列到倒数第二列，因为我数据集为一元的，所以这里只有一列
    Y = data[:, -1] #Y保存数据集最后一列
    row_num = len(Y) #总数据行数
    col_num = data.shape[1] #列数，一元线性规划只有两列
    #X, Min, max_min = featureNormalize(X) #这个函数在这没用到，实际上是用来特征放缩的，当数据集是多元，并且某些个x差值很大的时候进行特征放缩
    XX = np.hstack((np.ones((row_num,1)), X)) #给X扩容，加上一列1，因为目标函数为y=ax+b的形式，b就是常数，系数矩阵对应的x为1
    #print('梯度下降...')

    theta = np.zeros((col_num, 1)) #初始化theta为0
    Y = Y.reshape(-1,1) #将Y转为列向量
    theta = gradientDescent(XX,Y,theta,alpha,iters) #梯度下降法来实现线性回归，返回训练生成的系数矩阵
    print('梯度下降解的theta的值为:')
    print(theta)
    plot_figure(theta, X, Y, 'linear1.png')

    theta = normalEquation(XX, Y)
    print('正规方程解的theta的值为:')
    print(theta)

    plot_figure(theta, X, Y, 'linear2.png') #画图
    return theta



def featureNormalize(X):
    X_Norm = np.array(X) #把X变为np矩阵
    #print(X_Norm)
    Min = X_Norm.min(0)
    Max = X_Norm.max(0)
    #print(average)
    max_min = Max - Min #求最大值减最小值
    #print(max_min)
    for i in range(X.shape[1]): #更新每一列的数据
        X_Norm[:, i] = (X_Norm[:, i] - Min[i]) / max_min[i] #归一化
    return X_Norm, Min, max_min

def plot_figure(theta, X, Y, name): #画最后的拟合直线
    plt.scatter(X, Y,s=10)
    x = np.linspace(5,23,100)
    y = theta[0] + theta[1]*x
    plt.plot(x,y,'r')
    plt.savefig(name)
    plt.show()

def gradientDescent(X, Y, theta, alpha, iters): #梯度下降函数
    raw_num = len(Y)
    for i in range(iters): #迭代不断更新系数
        h = np.dot(X, theta) #每次预测的值
        theta = theta - (alpha/raw_num) * (np.dot(np.transpose(X), h - Y))
    return theta

def predict(theta, Min, max_min):
    pre_num = np.array([1650, 3])
    pre_num = (pre_num - Min) / max_min
    pre_num = np.hstack((np.ones((1)), pre_num))
    result = np.dot(pre_num, theta)
    return result

def normalEquation(X, Y):
    theta = np.dot(np.linalg.inv(np.dot(X.T, X)), np.dot(X.T, Y))
    return theta


linearRegression()