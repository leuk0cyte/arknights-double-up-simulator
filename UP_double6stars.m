% written by leuk0cyte, 2020
% һ�ֳ�ȡ�Ķ��壺�Գ�����Ǻ����һ�γ�ȡ��ʼ������һ�γ�����ǣ��ù��̳�Ϊһ�ֳ�ȡ
% �磬XX����һ�����ǳ�����ֽ�����80�γ�ȡ�ų鵽Ψһһ������-���飬���ǳ�֮Ϊ
% ��ȡ��Ϊ80��һ�ֳ�ȡ
tic;

p0 = 0.02; % ������ǵ�ԭʼ����
p1 = 0.02; % 50���ĸ��ʲ���
p2 = 0.7; % ���up�����ǵĸ���
p3 = 0.5; % up�У���ĸ���
p4 = 1-p3; % up�У����ĸ���
N = 1e6; % ���Դ���

p = zeros([1 99]); % һ�ֳ�ȡ�У���n������ǵĸ���
for i = 1:50
    p(i) = p0;
end
for i = 51:99
    p(i) = p0 + p1*(i-50);
end

X = zeros([1 N]);
for i = 1:N % ����ѭ��
    flag = ones([1 2]);
    k = 0;
    while sum(flag) ~= 0
        for j = 1:99
            if randtest(p(j))==1 % �������
                k = k + j; % ���׼���������
                if randtest(p2)==1 % ���up
                    if randtest(p3)==1 % �����
                        flag(1) = 0;
                        break; % ����ѭ���������Ƿ�����ж�
                    else
                        flag(2) = 0; % �����
                        break;
                    end
                end
            end
        end
    end
    X(i) = k;
end

Y = zeros([2 max(X)-min(X)+1]); % ��һ��Ϊ�������õĳ�ȡ�����ڶ���Ϊ�ڸó�ȡ����ǡ�ó�����������
Y(1,:) = min(X):max(X);
for i = 1:length(Y(1,:))
    Y(2,i) = sum(X(:)==Y(1,i));
end

Z = Y; % ��һ��Ϊ�������õĳ�ȡ�����ڶ���Ϊ�ڸó�ȡ���ڳ����Ƶ��
for i = 1:length(Y(1,:))
    Z(2,i) = sum(Y(2,1:i))/N;
end

E = Y(1,:)*Y(2,:)'/N;
% ����˫up����ѧ����

plot(Z(1,:),Z(2,:));
xlim([2,600]);
title('�����Ƶ��V.S.������ȡ�Ĵ���@һ�����ʵ�飬��Ͱ��ȸ���')
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