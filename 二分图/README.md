最小点覆盖 = 最大匹配 = 点总数 - 最大独立集  = 点总数 - 最小路径点覆盖 <br/><br/>

最大独立集 : 选出最多的点，每两点之间没有边 (等价去掉最少的点，把所有边都破坏掉) <br/><br/>

最小点覆盖 ： 用最少的点，让每条边都至少和其中的一个点 <br/><br/>

最小路径点覆盖 ： 在图G中找出一些路径，每条路径从起点走到终点，使所有点均被覆盖，且只被覆盖一次，选出的这些路径组成路径覆盖。 如果找出最少的路径成为一个路径覆盖，则称为最小路径覆盖。
