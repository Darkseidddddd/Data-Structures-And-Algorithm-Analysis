import numpy as np
from matplotlib import pyplot as plt
from matplotlib.font_manager import FontProperties

font = FontProperties(fname=r"c:\windows\fonts\simsun.ttc", size=14)

def sigmoid(z): #sigmoid函数
    return 1 / (1 + np.exp(-z))

def cost(theta, X, Y): #代价函数
    theta = np.matrix(theta)
    X = np.matrix(X)
    Y = np.matrix(Y)
    first = np.multiply(-Y, np.log(sigmoid(X*theta)))
    second = np.multiply((1-Y), np.log(1 - sigmoid(X*theta)))
    return np.sum((first - second) / len(Y))

def featureNormalize(X): #特征归一化，根据数据选择
    X = np.array(X)
    Min = X.min(0)
    Max = X.max(0)
    Max_Min = Max - Min
    for i in range(X.shape[1]):
        X[:, i] = (X[:, i] - Min[i]) / Max_Min[i]
    return X, Min, Max_Min

def gradientDescent(X, Y, theta, alpha, iters): #梯度下降法
    raw_num = len(Y)
    J_history = np.zeros((iters, 1))

    for i in range(iters):
        h = sigmoid(np.dot(X, theta))
        J_history[i] = cost(theta, X, Y)
        theta = theta - (alpha/raw_num) * (np.dot(np.transpose(X), h - Y))

    return theta, J_history

def logisticRegression(alpha = 0.3, iters = 6000): #逻辑回归主函数
    data = np.loadtxt("ex2data1.txt", delimiter=',')
    X = data[:, 0 : -1]
    Y = data[:, -1]
    raw_num = len(Y)
    col_num = data.shape[1]
    #plot_X1_X2(X, Y)


    X, Min, Max_Min = featureNormalize(X)
    plot_X1_X2(X, Y)
    X = np.hstack((np.ones((raw_num, 1)), X))
    Y = Y.reshape(-1,1)
    theta = np.zeros((col_num, 1))
    theta, J_history = gradientDescent(X, Y, theta,  alpha, iters)
    print(theta)
    plot_figure(theta)
    plotJ(J_history, iters)


def plot_X1_X2(X, Y): #画散点图
    X1 = X[3]
    X2 = X[0]

    for i in range(len(Y)):
        if Y[i] == 1:
            X1 = np.vstack((X1, X[i]))
        else:
            X2 = np.vstack((X2, X[i]))

    plt.scatter(X1[:,0], X1[:,1], c = 'b')
    plt.scatter(X2[:,0], X2[:,1], c = 'r')
    #plt.savefig('ex2output1.png')
    #plt.show()

def plot_figure(theta): #画最后拟合的图像
    x = np.linspace(0,1)
    y = -(theta[0] + theta[1]*x)/theta[2]
    plt.plot(x, y, 'black')
    plt.savefig('ex2output2.png')
    plt.show()

def plotJ(J_history, num_iters): #画代价函数随着迭代次数梯度下降的过程
    x = np.arange(1, num_iters + 1)
    plt.plot(x, J_history)
    plt.xlabel(u"迭代次数", fontproperties=font)  # 注意指定字体，要不然出现乱码问题
    plt.ylabel(u"代价值", fontproperties=font)
    plt.title(u"代价随迭代次数的变化", fontproperties=font)
    plt.savefig('ex2output3.png')
    plt.show()


logisticRegression()
#print(np.array([0,0]))

