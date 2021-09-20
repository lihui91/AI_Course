from re import compile     #正则表达式
from copy import deepcopy  #deepcopy函数


class Unit:
    """

    Unit是表达式中最基本的单元，其遵循以下规则：
    1) 所有名字皆为英文字母和_的组合
    2) 代表变量需要在变量名前加上*
    eg: fun(a, *b)，fun代表函数，a代表常量，*b代表变量
    """
    _pattern = compile(r'^\s*(.*)\s*\((.*)\)\s*$') #正则表达式验证是否为函数
    _name_pattern = compile(r'^\w+$')#函数名（过程名）
    _arg_pattern = compile(r'^\*?\w+$')#变量和常量

    @classmethod #不需要实例化即可调用
    def is_variable(cls, arg: str) -> bool:
        return arg.startswith('*')

    def __init__(self, unit: str):
        """
        初始化函数
        确定Unit的函数名，变量/常量列表
        """
        res = Unit._pattern.match(unit) #函数

        assert Unit._name_pattern.match(res.group(1)),res  #函数匹配正确则继续匹配函数名
        self.name = res.group(1)#函数名（过程名）

        self.args = [] #常/变量数组
        for each in res.group(2).split(','):
            each = each.strip()
            res = Unit._arg_pattern.match(each)
            self.args.append(res.group())

    def update_args(self, mapping: dict):
        #置换过程中替换变量
        for i in range(len(self.args)):
            self.args[i] = mapping.get(self.args[i], self.args[i])
    def mapping_args(self, other):
        """
        寻找可置换的过程（函数）
        self和other，分别需要修改什么变量，以other的为主
        如果self中一个全体变量对应other中的多个全体变量，那么other中需要将其统一
        eg: f(*a, *b, c, *b) mapping_args f(d, *e, *f, *g)
            *b 对应 *e和*g，所以other需要将*e改为*g
            返回 ({'*a':'d', '*b':'*g'},{'*f':'c', '*e':'*g'})
        """
        if not isinstance(other, Unit):
            return None
        if self.name != other.name:
            return None
        if len(self.args) != len(other.args):
            return None

        self_map = {}#被置换的是self,事实的unit
        other_map = {}#被置换的是other,目标的unit
        for s, o in zip(self.args, other.args):
            s_is_global = Unit.is_variable(s)#事实，是否含有变量
            o_is_global = Unit.is_variable(o)#目标，是否含有变量
            if s_is_global:
                # self_map中可能存在一个全体映射到多个个体的可能，用集合收集起来
                self_map[s] = self_map.get(s, set())
                self_map[s].add(o)
            elif o_is_global:
                # other_map只存在从全体映射到个体的可能
                if other_map.get(o, s) != s:#目标未被置换
                    return None
                other_map[o] = s
            elif s != o:
                return None

        for k, v in self_map.items():
            if len(v) == 1:
                self_map[k] = v.pop()
            else:
                # k存在多个映射，以某种方式将他们进行排序，然后取li[-1]作为最终映射目标
                li = sorted(list(v), key=lambda t: t)
                self_map[k] = li[-1]
                for i in range(len(li) - 1):
                    if other_map.get(li[i], li[-1]) != li[-1]:
                        return None
                    other_map[li[i]] = li[-1]

        return self_map, other_map

    def __eq__(self, other):
        """
        :type other: Expression
        """
        if not isinstance(other, Unit):
            return False
        return str(self) == str(other)

    def __str__(self):
        return self.name + '(' + ','.join(self.args) + ')'


class Expression:
    """
    表达式在推理机中组成库，原则：
    Unit<-Unit1^Unit2^.^UnitN
    将表达式分解成Unit
    """
    _pattern = compile(r'^(.*)<-(.*)$')

    def __init__(self, expression: str):
        res = Expression._pattern.match(expression)
        #head是蕴含式的后件，目标的head为None
        self.head = None if res.group(1).strip() == '' else Unit(res.group(1))

        self.body = [] #unit数组
        if res.group(2).strip() != '':
            for each in res.group(2).split('^'):
                self.body.append(Unit(each))

    def update_args(self, mapping: dict):
        #用mapping中的置换对，更新表达式
        if self.head:
            self.head.update_args(mapping)
        for each in self.body:
            each.update_args(mapping)

    def remove_all_from_body(self, unit: Unit):
        """
        清除表达式中所有unit
        """
        for i in range(self.body.count(unit)):
            self.body.remove(unit)

    def clear_same_unit(self):
        """
        移除相同的unit
        """
        for i, v in enumerate(self.body):
            if self.body.index(v) != i:
                self.body.pop(i)

    def mgu(self, other, limit=None):
        """
        置换合一，利用过程更新目标
        self和other的归结结果
        self是目标（待证明）
        :param limit:
        :type other: Expression
        """
        if not isinstance(other, Expression):
            return None

        if self.head or not other.head:
            return None

        if limit is None:
            limit = self.body

        for i, v in enumerate(limit):
            # 匹配目标与过程的head，进行置换合一

            res = other.head.mapping_args(v)
            if not res:
                continue
            other_map, self_map = res
            if not self_map:
                self_copy = Expression('<-')
                self_copy.body = self.body[:]
                to_remove = v
            else:
                self_copy = deepcopy(self)
                self_copy.update_args(self_map)
                to_remove = deepcopy(v)
                to_remove.update_args(self_map)

            if not other_map:
                other_copy = Expression('<-')
                other_copy.body = other.body[:]
            else:
                other_copy = deepcopy(other)
                other_copy.head = None
                other_copy.update_args(other_map)

            other_copy.body.extend(self_copy.body)
            other_copy.remove_all_from_body(to_remove)
            other_copy.clear_same_unit()
            return other_copy

        return None

    def __str__(self):
        return (str(self.head) if self.head else '') + '<-' + (
            '^'.join(str(each) for each in self.body) if len(self.body) else '')


class Engine:
    def __init__(self, lib):
        """
        type：horn语句数组
        输入事实和过程数组，归结法证明目标成立
        """
        self.lib = [Expression(each) for each in lib]#过程体

    def resolution(self, exp: Expression):
        #归结过程
        if exp.head:#目标带有后件，不符合horn子句规则
            return None

        if not exp.body:#空语句，停止递归
            return []

        for each in self.lib:
            # 如果这一个证明步骤是可行的，那么关于exp.body[0]总会有一条规则可以消除它
            # 如果无法消除，那么直接返回
            res = exp.mgu(each, [exp.body[0]])#置换合一
            if res:#非空表示可置换，返回新目标
                ret = self.resolution(res)#递归证明置换后的新目标，返回一条证明步骤
                if ret is not None:
                    ret.insert(0, (each, res))#each:结合的事实，res:生成的目标
                    return ret

        return None

    def proof(self, exp: str):
        """
        返回归结过程，如果证明失败，则返回None
        exp:目标
        """
        exp = Expression(exp)#目标
        self.lib.append(exp)#在数组中加入目标
        ret = self.resolution(exp)
        self.lib.pop()
        return ret
