/*动态规划经典问题汇总
# 最大连续子序列和
# 最长不下降子序列（LIS）
# 最长公共子序列 （LCS）
# 最长回文子串 
# DAG最长路
# 背包
  ## 01背包
  ## 完全背包
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;

namespace DynamicPlanning {
	class DP {
	public:
		/// <summary>
		/// 问题描述： 给定数字序列A1....An(无大小序且有正负值), 求Ai+...+Aj最大，输出最大值
		/// 思路：从题意中可以感觉，这个题有点移动窗口的味道，但是窗口大小是不固定的。 
		///		 提取一些关键词，子序列是连续的，求和。我们可以考虑算出每种情况的值作比较
		///		 但是计算每种情况时，我们可能会产生重复计算前一个序列和（这正是动态规划所要消去的）
		///		 在每次求和中，每次求和时，若之前的数的最大的和加上当前的值小于当前值时，我们就要舍弃之前的和，从当前值重新计算
		///		 故我们可以推断出这个状态方程式 f(i) = max(f(i-1)+a[i], a[i])
		/// 复杂度：由于比较了N次，故时间O(N)，同时我们也用了一个数组来存放值（用双指针的话，就没有空间复杂度了），故空间为O(N);
		/// </summary>
		template<typename T> T LCSS(vector<T> v) {
			int len = v.size();
			vector<T> dp(len);

			dp[0] = v[0];

			for (int i = 1; i < len; ++i) {
				
				//状态转移方程
				dp[i] = max(dp[i - 1]+v[i], v[i]);
			}

			T max = dp[0];
			for (int i = 1; i < len; ++i) {

				//寻找dp中的最大值(可以合并到上一个for循环里)
				if (dp[i] > max) {
					max = dp[i];
				}
			}
			return max;
		}

		/// <summary>
		 //问题描述：在一个序列中，找到一个最长的子序列（可以不连续），使得这个子序列是不下降（非递减）的
		 //思路：首先我们提取一些关键字，最长不连续的子序列，要呈递减
		 //     那我们需要遍历数组内的值，然后和之前形成的序列进行对比，如果当前值比之前的序列小了，就从一开始重新开始计数
		 //     这里面我涉及到的重复操作，就是重复判断了是否和之前已有最长序列形成最长序列。
		 //     故我们推断出这个状态方程式 f(i) = max(1, f(j)+1), i表示元素为结尾要记录的序列长度，j表示之前已知的序列长度
		 //复杂度：由于我们遍历原序列，同时要和之前的dp数组内已有的值进行对比，故时间O(N2)，空间为O(N)
		/// </summary>
		template<typename T> int LIS(vector<T> v) {
			int len = v.size();
			vector<T> dp(len);
			
			int res = -1;
			for (int i = 0; i < len; ++i) {
				dp[i] = 1;
				for (int j = 0; j < i; ++j) {

					//保证当前值大于之前的每个值，更新最大子序列长度
					if (v[i] >= v[j] && (dp[j] + 1 > dp[i])) {
						dp[i] = dp[j] + 1;
					}
				}

				res = max(res, dp[i]);
			}
			return res;
		}

		/// <summary>
		 //问题描述： 给定两个字符串（或数字序列）A和B，求一个字符串，使得这个字符串是A和B的最长公共部分（子序列可以不连续）
		 //思路：提取关键字：最长公共部分，可以是不连续的
		 //     同样的，我们需要遍历两个序列，然后以其中一种序列为基准不断地去对比另外一个序列
		 //     这里面涉及到的重复操作，就是我们总会不断去比较之前比过的元素，换言之就是重新将新元素与旧元素重新拼起来，再去找对应的公共部分
			//	 故，我们需要保存之前对比过最大公共部分，我们可以创建dp[i][j]-> 截止序列1中第i个元素和截止序列2中第j个元素（注意它们可以不相等，不要先入为主）
		 //     当第i个元素和第j和元素，相等，我们得出：dp[i][j] = dp[i-1][j-1]+1; 
			//	 若不等（两个同时加入新元素不等），我们只需要继承之前的公共部分，
		 //     这时候要比较两种情况，只有序列1加入一个新元素的公共部分和只有序列2加入了一个新元素的公共部分哪个长，然后我们取其长就可以了
		 //     由此可得转换表达式：dp[i][j] = max(dp[i][j-1], dp[i][j-1])
		 //复杂度：比较两个序列，时间复杂度：O(NM), 空间复杂度：O(NM)
		/// </summary>
		template<typename T1>int LCS(T1 s1, T1 s2) {
			int len1 = s1.size();
			int len2 = s2.size();
			vector<vector<int>> dp = vector<vector<int>>(len1, vector<int>(len2));

			//边界处初始化
			for (int i = 0; i < len1; ++i) {
				if (s1[i] == s2[0])
					dp[i][0] = 1;
				else
					dp[i][0] = 0;
			}

			for (int i = 0; i < len2; ++i) {
				if (s1[0] == s2[i])
					dp[0][i] = 1;
				else
					dp[0][i] = 0;
			}

			//状态方程
			for (int i = 1; i < len1; ++i) {
				for (int j = 1; j < len2; ++j) {
					if (s1[i] != s2[j]) {
						dp[i][j] = max(dp[i - 1][j], dp[i][j-1]);
					}
					else {
						dp[i][j] = dp[i - 1][j - 1] + 1;
					}
				}
			}

			return dp[len1-1][len2-1];
		}

		/// <summary>
		/// 问题描述：给出一个字符串S，求S的最长回文字串的长度
		/// 思路：提取关键字：最长回文，（隐藏条件：连续）
		///      一般情况，当我们不断提取字串时，我们要不停的对新子串进行判断。
		///      这时我们会发现，如果新字串的两头相等，且除去两头的中间部分是回文的话，那么这个字串就是回文，反之，则不是
		///      所以我们可以得到这样状态方程，若相等且中间部分是回文：dp[i][j] = dp[i+1][j-1] +2；若不等，dp[i][j] = 1;
		/// 复杂度：由于要遍历一次序列，且改变字串长度后又要重新遍历序列，故时间O(N2), 空间，O(N2)
		/// </summary>
		template<typename T> int LCS(T s) {
			int len = s.size();
			vector<vector<int>> dp = vector<vector<int>>(len, vector<int>(len));
			
			//边界初始化,对角线的回文长度都为1
			for (int i = 0; i < len; ++i) {
				dp[i][i] = 1;
			}

			int max = -1;
			//状态转移
			for (int i = 1; i < len; ++i) {
				for (int j = 0; j+i < len; ++j) {
					if (s[j] == s[j+i]) {
						dp[j][j+i] = dp[j+ 1][j +i- 1] + 2;
						
						max = max > dp[j][j + i] ? max : dp[j][j + i];
					}
					else {
						dp[j][j+i] = 1;
					}
				}
			}
			return max;
		}

		/// <summary>
		/// 问题描述：给定一个有向无环图，求出路径和最大的那一条
		///	思路: 提取关键字： 有向无环图， 路径和最大
		///		 因此我们需要记录每个点到终点的权值和，且保存该点最大的一条路径
		/// 
		/// </summary>
		template<typename T> int DAG(T s) {
			if (dp[i] > 0) return dp[i];    //若发现该点有值，就推出递归返回该值

			for (int j = 0; j < n; ++j) {   
				if (G[i][j] != 0) {           //G[][]为邻接矩阵， 
					int temp = DAG(i) + Gp[i][j]);    //计算当前点到后续下一个结点的最大值

					if (temp > dp[i]) {
						dp[i] = temp;           //若值大，更新dp和当前结点的路线
						choice[i] = j;
					}
				}
			}
			return dp[i];
		}

		/// <summary>
		/// 问题：有n件物品，每件物品重w[i], 价格为c[i]。现在有一个容量为v的背包，问如何选取物品放入背包，使得背包内物品的总价值最大。其中每种物品都只有一件。
		/// 思路：提取关键字，每个物品只有一件， 总价值最大
		///		 通常情况，我们要不断尝试放物品进，然后不停试它的临界值并使价值可以达到最大。为了省去重复的计算，我需要记录下每种容量下的价值和。
		///		 这时我们可以发现，若当我们不放一个物件，那说明当前背包就是当前最大容量，那么当前总价值就为最大值。若放了它，那说明当前背包在没放这个物件的情况下，总价值就为最大。
		///      故我们可以这样表示状态方程：dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - w[i]] + c[i])
		/// 复杂度：由于要遍历两次数组，故时间复杂度O(NM), 空间复杂度：#1, O(NM), #2, O(N)
		/// </summary>
		template<typename T1, typename T2> T2 bag_01(int n, vector<T1> w, vector<T2> c, T1 V) {
			//vector<vector<T1>> dp = vector<vector<int>>(n, vector<T1>(V+1));
			//
			////边界初始化
			//dp[0][w[0]] = c[0];

			//T2 max_val = c[0];
			////状态方程
			//for (int i = 1; i < n; ++i) {
			//	for (int v = w[i]; v <= V; ++v) {
			//		dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - w[i]] + c[i]);

			//		max_val = max(max_val, dp[i][v]);
			//	}
			//}

			//使用滚动数组(逆序)
			vector<T1> dp(V + 1);
			T2 max_val = c[0];
			//状态方程
			for (int i = 0; i < n; ++i) {
				for (int v = V; v >= w[i]; --v) {
					dp[v] = max(dp[v], dp[v - w[i]] + c[i]);
					max_val = max(max_val, dp[v]);
				}
			}
			
			return max_val;
		}

		/// <summary>
		/// 完全背包和01背包类似，但是不同点是它的一种物品可以有多个。
		/// 故当我们决定放第i个物品时，我们可以继续放入该物品，所以不用考虑之前的情况
		/// </summary>
		template<typename T1, typename T2> int bag_full(int n, vector<T1> w, vector<T2> c, T1 V) {
			vector<vector<T1>> dp = vector<vector<T1>>(n, vector<int>(V + 1));

			dp[0][w[0]] = c[0];

			T2 max_val = c[0];
			for (int i = 1; i < n; ++i) {
				for (int v = w[i]; v <= V; ++v) {
					dp[i][v] = max(dp[i - 1][v], dp[i][v - w[i]] + c[i]);

					max_val = max(max_val, dp[i][v]);
				}
			}

			//使用滚动数组(正序)
			//vector<T1> dp(V + 1);
			//T2 max_val = c[0];
			////状态方程
			//for (int i = 0; i < n; ++i) {
			//	for (int v = V; v >= w[i]; --v) {
			//		dp[v] = max(dp[v], dp[v - w[i]] + c[i]);
			//		max_val = max(max_val, dp[v]);
			//	}
			//}

			return max_val;
		}
	};
}
