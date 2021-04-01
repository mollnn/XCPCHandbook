目录- <a href="#概念理解与经典类型">概念理解与经典类型</a>- <a href="#bzoj1398-寻找主人-necklace">[BZOJ1398] 寻找主人 Necklace</a>- <a href="#sp7258-sublex">[SP7258] SUBLEX </a>- <a href="#hdu5769-substring">[HDU5769] Substring</a>- <a href="#hdu4436-str2int">[HDU4436] str2int</a>- <a href="#sp1811-lcs">[SP1811] LCS</a>- <a href="#loj171-最长公共子串">[LOJ171] 最长公共子串</a>- <a href="#sdoi2016-生成魔咒">[SDOI2016] 生成魔咒</a>- <a href="#jsoi2012-玄武密码">[JSOI2012] 玄武密码</a>- <a href="#bjwc2010-外星联络">[BJWC2010] 外星联络</a>- <a href="#usaco2006-dec-milk-patterns">[Usaco2006 Dec] Milk Patterns</a>- <a href="#hdu4622-reincarnation">[HDU4622] Reincarnation</a>- <a href="#hdu4416-good-article-good-sentence">[HDU4416] Good Article Good sentence</a>- <a href="#bzoj2780-sevenk-love-oimaster">[BZOJ2780] Sevenk Love Oimaster</a>- <a href="#usaco10dec-threatening-letter-g">[Usaco10Dec] Threatening Letter G</a>- <a href="#综合运用">综合运用</a>- <a href="#bzoj2555-substring">[BZOJ2555] SubString</a>- <a href="#wannafly-camp-2020-day-2d-卡拉巴什的字符串">Wannafly Camp 2020 Day 2D 卡拉巴什的字符串</a>- <a href="#bzoj1396-识别子串">[BZOJ1396] 识别子串</a>- <a href="#cf149e-martian-strings">[CF149E] Martian Strings</a>- <a href="#bzoj2119-股市的预测">[BZOJ2119] 股市的预测</a>- <a href="#p6292-区间本质不同子串个数">[P6292] 区间本质不同子串个数</a>- <a href="#广义-sam-应用">广义 SAM 应用</a>- <a href="#p6139-【模板】广义后缀自动机">[P6139] 【模板】广义后缀自动机</a>- <a href="#zjoi2015-诸神眷顾的幻想乡">[ZJOI2015] 诸神眷顾的幻想乡</a>- <a href="#cf427d-match--catch">[CF427D] Match & Catch</a>
### 概念理解与经典类型
#### [<a href="https://www.cnblogs.com/mollnn/p/13282872.html" target="_blank">BZOJ1398] 寻找主人 Necklace</a>
<blockquote>
给定 $S,T$，判断其是否循环同构，如果是则输出最小表示。
</blockquote>
直接用 SAM 求最小表示比较是否相等即可。
#### <a href="https://www.cnblogs.com/mollnn/p/12370496.html" target="_blank">[SP7258] SUBLEX </a>
<blockquote>
求给定主串的所有本质不同子串中第 $k$ 小子串。
</blockquote>
本质不同子串集合和 SAM 的转移边路径集合构成双射，按拓扑逆序计算每个点发出的路径数，跑 kth 即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13293743.html" target="_blank">HDU5769] Substring</a>
<blockquote>
求一个串种包含某个特定字符的本质不同子串有多少种。
</blockquote>
设 f[p] 表示从结点 p 出发沿着转移边走能到达的合法的本质不同子串有多少种，设题中要走的字母为 c，对于 p 通过 c 转移到 q，f[p]+=siz[q]；对于其它字符，f[p]+=f[q]，其中 siz[p] 表示 p 出发可以转移到的本质不同子串数目，按照拓扑逆序统计即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13584939.html" target="_blank">HDU4436] str2int</a>
<blockquote>
给定若干字符串，每个字符串中所有子串转化为数字，放在一起去重后，求它们的和 $\bmod 2012$。
</blockquote>
如果能处理好前导零那么就是本质不同子串化数求和。将各个数字串用奇怪字符连接起来建立 SAM，对 i 设从根到达它的路径数量为 f[i]，它代表的本质不同子串转化为数字后的和为 g[i]，对于 i 经过 c 到 j，有 f[j]+=f[i], g[j]+=10g[i]+c*f[i]。为了处理前导零，在根结点转移出去时，跳过 0 转移即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13174124.html" target="_blank">SP1811] LCS</a>
<blockquote>
求两个字符串的最长公共子串。
</blockquote>
对 A 建立 SAM，将 B 扔到上面跑，记录当前结点 $p$ 和匹配长度 $l$，能走 trans 边则走，否则沿着 link 跳并让 $l$ 对 $len[p]$ 取 $\min$，则 $l$ 的历史最大值即为答案。
#### [<a href="https://www.cnblogs.com/mollnn/p/13175736.html" target="_blank">LOJ171] 最长公共子串</a>
<blockquote>
求多个字符串的最长公共子串。
</blockquote>
沿用 [SP1811] 的思路，选出最短串建 SAM，对每个节点记录各个串跑时匹配长度的最小值。
每个串跑时，节点先记录本轮匹配的最大值，再按拓扑逆序上传，最后更新记录的最小值。
#### [<a href="https://www.cnblogs.com/mollnn/p/13179313.html" target="_blank">SDOI2016] 生成魔咒</a>
<blockquote>
按顺序在一个序列的末尾插入数字，求每次插入后的本质不同子串个数。
</blockquote>
后缀自动机增量构造时，已经有的结点的 len 是不会再变化的，而 nq 结点不会产生贡献，于是每次加上 len[last]-len[link[last]] 即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13179689.html" target="_blank">JSOI2012] 玄武密码</a>
<blockquote>
给定一个基础串 S 和若干询问串 T，对于每个 T 求出其最长前缀 P 满足 P 是 S 的子串。
</blockquote>
SAM 是能接受所有 S 子串的自动机，因此将每个 T 丢上去跑，只能走转移边，走不动时就是答案
#### [<a href="https://www.cnblogs.com/mollnn/p/13287049.html" target="_blank">BJWC2010] 外星联络</a>
<blockquote>
求字符串中出现次数大于 1 的所有本质不同子串的出现次数。
</blockquote>
建出 SAM 后 DFS 并输出 endpos 集合大小。
#### [<a href="https://www.cnblogs.com/mollnn/p/13282944.html" target="_blank">Usaco2006 Dec] Milk Patterns</a>
<blockquote>
给定串 $S$ 求出现至少 $k$ 次的子串的最大长度。
</blockquote>
出现次数即 endpos 集合大小，基数排序预处理即可。所有满足条件的节点 len 中取最大即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13583496.html" target="_blank">HDU4622] Reincarnation</a>
<blockquote>
区间询问本质不同子串个数。要求 $O(n^2)$。
</blockquote>
暴力枚举起点，增量构造，即得到所有区间的答案。（优化做法见后）
#### [<a href="https://www.cnblogs.com/mollnn/p/13591985.html" target="_blank">HDU4416] Good Article Good sentence</a>
<blockquote>
给定 $S$ 和若干模式串 $T_i$，问 $S$ 的子串中有多少不是任何一个 $T_i$ 的子串。
</blockquote>
对 S 建立 SAM，$T_i$ 跑到 p 时，匹配长度为 l，则该结点及其后缀链接上所有结点所表示的长度 $\le l$ 的子串都应当被抛弃。考虑对每个结点维护一个匹配过的最大长度 f[i]，每次在匹配位置标记，最后按拓扑逆序上传取 max。统计 i 点的答案时，贡献为 len[i]-max(f[i],minlen[i])。
#### [<a href="https://www.cnblogs.com/mollnn/p/13597223.html" target="_blank">BZOJ2780] Sevenk Love Oimaster</a>
<blockquote>
给定若干主串和若干询问，每次询问一个字符串在多少个主串中作为子串出现过。
</blockquote>
对主串构建广义 SAM，求出每个结点在多少个主串中出现过，记为 f[i]。求解时可以暴力沿着后缀链接跳，但为了防止记重同时降低复杂度，需要记录每个结点在本轮中是否被访问过，碰到访问过的就结束。对于询问串扔到自动机上跑，设跑到了 p 则答案为 f[p]。
#### [<a href="https://www.cnblogs.com/mollnn/p/13283082.html" target="_blank">Usaco10Dec] Threatening Letter G</a>
<blockquote>
给定 $s_1,s_2$，问至少需要多少个 $s_1$ 的子串才能拼接成 $s_2$。
</blockquote>
贪心，对 $s_2$ 从左到右扫，能分在上一段里必然不会更劣，于是让 $s_2$ 在 $s_1$ 的 SAM 上贪心地沿着转移边跑，跑不动了就记答案并回到根。
### 综合运用
#### [<a href="https://www.cnblogs.com/mollnn/p/13274446.html" target="_blank">BZOJ2555] SubString</a>
<blockquote>
给定一个初始串，支持两种操作：在当前串后面加上一个串；询问一个串在当前串中作为子串出现次数。
</blockquote>
询问即后缀链接树的子树大小，LCT 维护子树大小即可。
#### <a href="https://www.cnblogs.com/mollnn/p/12335662.html" target="_blank">Wannafly Camp 2020 Day 2D 卡拉巴什的字符串</a>
<blockquote>
动态维护任意两个后缀的 $lcp$ 集合的 $mex$，支持在串末尾追加字符。
</blockquote>
显然答案单调增。LCP 即后缀链接上的 LCA 的 maxlen，一个结点可能成为 LCP 当且仅当它有儿子。修改父子关系时在桶上暴力维护即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13282787.html" target="_blank">BZOJ1396] 识别子串</a>
<blockquote>
给定 $S$，问其每一位的最短识别子串是多长，即包含这个字符且仅出现一次的串。
</blockquote>
建出 SAM，只有 endpos 大小为 1 的结点才有贡献，其范围一定是 [i,pos]，对 [pos-minlen+1,pos] 中的每个点产生 minlen 的贡献，对 [pos-maxlen+1,pos-minlen] 中的每个点产生 pos-i+1 的贡献。第一部分线段树直接维护，第二部分线段树维护 f[i]-i 即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13579835.html" target="_blank">CF149E] Martian Strings</a>
<blockquote>
给定主串 S 和若干询问，每次给定询问串 p，输出有多少个询问串，满足存在 S 的两个不相交的子串拼起来与 p 相等。
</blockquote>
询问串可行当且仅当存在 k 使得 p[1..k] 在主串中的最小结束位置 pre[k] 小于 p[k+1,l] 的最大开始位置 suf[k+1]。对 S 正反串分别建 SAM，通过按拓扑逆序上传预处理每个结点对应的 endpos 集合的最小值。将 p 扔到 SAM 上跑，只走转移边不走后缀链接，即可求出 pre,suf。
#### [<a href="https://www.cnblogs.com/mollnn/p/13283724.html" target="_blank">BZOJ2119] 股市的预测</a>
<blockquote>
寻找 $ABA$ 形式的子串数目，满足 $|B|=m$。
</blockquote>
枚举 $A$ 长度 $i$，将 $i,2i,3i,...$ 设置为关键点，分别考虑左侧的 $A$ 横跨每一个关键点时的情况，由于 $A$ 会且仅会横跨一个关键点，这样统计是不重不漏的。设枚举的关键点为 $p$，则右侧 $A$ 上与之对应的是 $p+i+m$，求出这两点的 $lcp,lcs$，则左侧 $A$ 块可以是区间 $[p-lcs+1,p+lcp-1]$，故可能位置有 $lcs+lcp-i$ 种。为了不重复，$lcs,lcp$ 要对 $i$ 取 min。求 $lcs,lcp$ 用 $SA$ 或 $SAM$ 上求 $LCA$ 均可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13619686.html" target="_blank">P6292] 区间本质不同子串个数</a>
<blockquote>
区间询问本质不同子串个数。要求 $O(n \log^2 n)$。
</blockquote>
考虑离线，将所有询问挂在右端点上，从左到右扫描整个序列，设扫描到的位置为 $r$。用线段树统计答案，第 i 位表示 S[1..r] 中最后一次出现在左端点为 i 位置的子串数，询问就是求 [l,r] 和。在新增字符 S[r] 时，会对 [1,r] 各产生 1 的贡献，由于某些 S[i..r] 在之前出现，为了去重，用 SAM 维护串，从 S[1..r] 对应节点沿着后缀链接跳，用经过所有节点上一次出现的右端点 lastpos 计算出发生重复的区间 [lastpos[p]-len[p]+1,lastpos-len[fa[p]]]，在线段树上 -1，并将 lastpos 设置为 r。考虑到 lastpos 相同的点可以一起处理，每次从当前位置跳到根的过程就是 Access 的过程，用 LCT 维护即可。
### 广义 SAM 应用
#### [<a href="https://www.cnblogs.com/mollnn/p/13289162.html" target="_blank">P6139] 【模板】广义后缀自动机</a>
<blockquote>
给定 $s_1,s_2,...,s_n$ 求本质不同子串个数。
</blockquote>
广义后缀自动机不只是将 $last$ 指回 $root$。建好自动机后像普通 SAM 那样统计答案。
#### [<a href="https://www.cnblogs.com/mollnn/p/13290277.html" target="_blank">ZJOI2015] 诸神眷顾的幻想乡</a>
<blockquote>
给定一棵叶子结点数量 $\le 20$ 的树，在树上任选一条路径，问有多少种颜色序列不同的选择。
</blockquote>
把每个叶子为根的树 DFS 一遍，当做 Trie 插入广义后缀自动机即可。
#### [<a href="https://www.cnblogs.com/mollnn/p/13581246.html" target="_blank">CF427D] Match & Catch</a>
<blockquote>
求在两个给定字符串中各只出现一次的最短公共子串。
</blockquote>
建立广义 SAM，对每个结点记录来源于各个串的 endpos 集合的大小，如果同为 1 则更新答案。