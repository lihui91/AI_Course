import horn

engine = horn.Engine([
    'live(A)<-',
    'live(B)<-',
    'live(C)<-',
    'hate(A,A)<-',
    'hate(A,C)<-',
    'live(*X)<-kill(*X,A)',
    'hate(*X,A)<-kill(*X,A)',
    'nhate(C,*X)<-hate(A,*X)',
    'hate(B,*X)<-richer(A,*X)',
    'hate(B,*X)<-hate(A,*X)',
    'richer(*X,A)<-nhate(B,*X)',
    'nhate(*X,A)<-hate(*X,B)^hate(*X,C)',
    'nhate(*X,B)<-hate(*X,A)^hate(*X,C)',
    'nhate(*X,C)<-hate(*X,A)^hate(*X,B)',
    'richer(*Y,*X)<-kill(*X,*Y)',
    'nkill(*X,*Y)<-richer(*X,*Y)',
    'nkill(*X,*Y)<-nhate(*X,*Y)',
])

process1 = engine.proof('<-nkill(B,A)^nkill(C,A)')#假设kill(A,A)
process2=  engine.proof('<-nkill(A,A)^nkill(C,A)')#假设kill(B,A)
process3=  engine.proof('<-nkill(B,A)^nkill(A,A)')#假设kill(C,A)


print('在一栋房子里发生了一件神秘的谋杀案，现在可以肯定以下几点事实：')
print('(a)在这栋房子里仅住有A,B,C三人；' )
print('(b)是住在这栋房子里的人杀了A； \n(c)谋杀者非常恨受害者； (d)A所恨的人，C一定不恨；')
print('(e)除了B以外，A恨所有的人； (f)B恨所有不比A富有的人； \n(g)A所恨的人，B也恨； (h)没有一个人恨所有的人；')
print('(i)杀人嫌疑犯一定不会比受害者富有。 \n为了推理需要，增加如下常识：(j)A不等于B。 ')
print('问：谋杀者是谁？\n')
print('live(x):x居住在这栋房子里')
print('hate(x,y):x恨y')
print('richer(x,y):x比y富有')
print('kill(x,y):x杀了y')
print('非用字母n表示')
print('')
process=[process3,process2,process1]
killer=["C","B","A"]
for i in range(3):
    print('证明：<-kill('+killer[i]+',A)')
    if process[i]:
        for reg, res in process[i]:
            print ('结合：', str (reg))
            print ('生成：', str (res))
        print ('得到空语句，结论成立，谋杀者是'+killer[i])
    else:
        print ('无法证明')
        print ('')
