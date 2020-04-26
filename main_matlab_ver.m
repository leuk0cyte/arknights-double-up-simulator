% written by leuk0cyte, 2020
% matlab 版本
% 一轮抽取的定义：自抽出六星后的下一次抽取伊始，到再一次抽出六星，该过程称为一轮抽取
% 如，XX自上一个六星抽出后，又进行了80次抽取才抽到唯一一个六星-闪灵，我们称之为
% 抽取数为80的一轮抽取
tic;

p0 = 0.02; % 获得六星的原始概率
p1 = 0.02; % 50抽后的概率补偿
p2 = 0.7; % 抽出up的六星的概率
p3 = 0.5; % up中，年的概率
p4 = 1-p3; % up中，阿的概率
N = 1e6; % 测试次数

p = zeros([1 99]); % 一轮抽取中，第n抽出六星的概率
for i = 1:50
    p(i) = p0;
end
for i = 51:99
    p(i) = p0 + p1*(i-50);
end

X = zeros([1 N]);
for i = 1:N % 测试循环
    flag = ones([1 2]);
    k = 0;
    while sum(flag) ~= 0
        for j = 1:99
            if randtest(p(j))==1 % 抽出六星
                k = k + j; 
                if randtest(p2)==1 % 抽出up
                    if randtest(p3)==1 % 抽出年
                        flag(1) = 0;
                        break; % 跳出循环，进行是否抽齐判断
                    else
                        flag(2) = 0; % 抽出阿
                        break;
                    end
                end
                break; % 保底计数器归零
            end
        end
    end
    X(i) = k;
end

Y = zeros([2 max(X)-min(X)+1]); % 第一排为抽齐所用的抽取数，第二排为在该抽取数下恰好抽齐的试验次数
Y(1,:) = min(X):max(X);
for i = 1:length(Y(1,:))
    Y(2,i) = sum(X(:)==Y(1,i));
end

Z = Y; % 第一排为抽齐所用的抽取数，第二排为在该抽取数内抽齐的频率
for i = 1:length(Y(1,:))
    Z(2,i) = sum(Y(2,1:i))/N;
end

E = Y(1,:)*Y(2,:)'/N;
fprintf("抽齐双up的数学期望为：%f",E);
% 抽齐双up的数学期望

plot(Z(1,:),Z(2,:));
xlim([2,600]);
title('抽齐的频率V.S.连续抽取的次数@一百万次实验，年和阿等概率')
toc;

function result = randtest(probility)
    if rand > probility
        result = 0;
        return;
    else
        result = 1;
        return;
    end
end
