/*��̬�滮�����������
# ������������к�
# ����½������У�LIS��
# ����������� ��LCS��
# ������Ӵ� 
# DAG�·
# ����
  ## 01����
  ## ��ȫ����
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
		/// ���������� ������������A1....An(�޴�С����������ֵ), ��Ai+...+Aj���������ֵ
		/// ˼·���������п��Ըо���������е��ƶ����ڵ�ζ�������Ǵ��ڴ�С�ǲ��̶��ġ� 
		///		 ��ȡһЩ�ؼ��ʣ��������������ģ���͡����ǿ��Կ������ÿ�������ֵ���Ƚ�
		///		 ���Ǽ���ÿ�����ʱ�����ǿ��ܻ�����ظ�����ǰһ�����кͣ������Ƕ�̬�滮��Ҫ��ȥ�ģ�
		///		 ��ÿ������У�ÿ�����ʱ����֮ǰ���������ĺͼ��ϵ�ǰ��ֵС�ڵ�ǰֵʱ�����Ǿ�Ҫ����֮ǰ�ĺͣ��ӵ�ǰֵ���¼���
		///		 �����ǿ����ƶϳ����״̬����ʽ f(i) = max(f(i-1)+a[i], a[i])
		/// ���Ӷȣ����ڱȽ���N�Σ���ʱ��O(N)��ͬʱ����Ҳ����һ�����������ֵ����˫ָ��Ļ�����û�пռ临�Ӷ��ˣ����ʿռ�ΪO(N);
		/// </summary>
		template<typename T> T LCSS(vector<T> v) {
			int len = v.size();
			vector<T> dp(len);

			dp[0] = v[0];

			for (int i = 1; i < len; ++i) {
				
				//״̬ת�Ʒ���
				dp[i] = max(dp[i - 1]+v[i], v[i]);
			}

			T max = dp[0];
			for (int i = 1; i < len; ++i) {

				//Ѱ��dp�е����ֵ(���Ժϲ�����һ��forѭ����)
				if (dp[i] > max) {
					max = dp[i];
				}
			}
			return max;
		}

		/// <summary>
		 //������������һ�������У��ҵ�һ����������У����Բ���������ʹ������������ǲ��½����ǵݼ�����
		 //˼·������������ȡһЩ�ؼ��֣���������������У�Ҫ�ʵݼ�
		 //     ��������Ҫ���������ڵ�ֵ��Ȼ���֮ǰ�γɵ����н��жԱȣ������ǰֵ��֮ǰ������С�ˣ��ʹ�һ��ʼ���¿�ʼ����
		 //     ���������漰�����ظ������������ظ��ж����Ƿ��֮ǰ����������γ�����С�
		 //     �������ƶϳ����״̬����ʽ f(i) = max(1, f(j)+1), i��ʾԪ��Ϊ��βҪ��¼�����г��ȣ�j��ʾ֮ǰ��֪�����г���
		 //���Ӷȣ��������Ǳ���ԭ���У�ͬʱҪ��֮ǰ��dp���������е�ֵ���жԱȣ���ʱ��O(N2)���ռ�ΪO(N)
		/// </summary>
		template<typename T> int LIS(vector<T> v) {
			int len = v.size();
			vector<T> dp(len);
			
			int res = -1;
			for (int i = 0; i < len; ++i) {
				dp[i] = 1;
				for (int j = 0; j < i; ++j) {

					//��֤��ǰֵ����֮ǰ��ÿ��ֵ��������������г���
					if (v[i] >= v[j] && (dp[j] + 1 > dp[i])) {
						dp[i] = dp[j] + 1;
					}
				}

				res = max(res, dp[i]);
			}
			return res;
		}

		/// <summary>
		 //���������� ���������ַ��������������У�A��B����һ���ַ�����ʹ������ַ�����A��B����������֣������п��Բ�������
		 //˼·����ȡ�ؼ��֣���������֣������ǲ�������
		 //     ͬ���ģ�������Ҫ�����������У�Ȼ��������һ������Ϊ��׼���ϵ�ȥ�Ա�����һ������
		 //     �������漰�����ظ����������������ܻ᲻��ȥ�Ƚ�֮ǰ�ȹ���Ԫ�أ�����֮�������½���Ԫ�����Ԫ������ƴ��������ȥ�Ҷ�Ӧ�Ĺ�������
			//	 �ʣ�������Ҫ����֮ǰ�Աȹ���󹫹����֣����ǿ��Դ���dp[i][j]-> ��ֹ����1�е�i��Ԫ�غͽ�ֹ����2�е�j��Ԫ�أ�ע�����ǿ��Բ���ȣ���Ҫ����Ϊ����
		 //     ����i��Ԫ�غ͵�j��Ԫ�أ���ȣ����ǵó���dp[i][j] = dp[i-1][j-1]+1; 
			//	 �����ȣ�����ͬʱ������Ԫ�ز��ȣ�������ֻ��Ҫ�̳�֮ǰ�Ĺ������֣�
		 //     ��ʱ��Ҫ�Ƚ����������ֻ������1����һ����Ԫ�صĹ������ֺ�ֻ������2������һ����Ԫ�صĹ��������ĸ�����Ȼ������ȡ�䳤�Ϳ�����
		 //     �ɴ˿ɵ�ת������ʽ��dp[i][j] = max(dp[i][j-1], dp[i][j-1])
		 //���Ӷȣ��Ƚ��������У�ʱ�临�Ӷȣ�O(NM), �ռ临�Ӷȣ�O(NM)
		/// </summary>
		template<typename T1>int LCS(T1 s1, T1 s2) {
			int len1 = s1.size();
			int len2 = s2.size();
			vector<vector<int>> dp = vector<vector<int>>(len1, vector<int>(len2));

			//�߽紦��ʼ��
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

			//״̬����
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
		/// ��������������һ���ַ���S����S��������ִ��ĳ���
		/// ˼·����ȡ�ؼ��֣�����ģ�������������������
		///      һ������������ǲ�����ȡ�ִ�ʱ������Ҫ��ͣ�Ķ����Ӵ������жϡ�
		///      ��ʱ���ǻᷢ�֣�������ִ�����ͷ��ȣ��ҳ�ȥ��ͷ���м䲿���ǻ��ĵĻ�����ô����ִ����ǻ��ģ���֮������
		///      �������ǿ��Եõ�����״̬���̣���������м䲿���ǻ��ģ�dp[i][j] = dp[i+1][j-1] +2�������ȣ�dp[i][j] = 1;
		/// ���Ӷȣ�����Ҫ����һ�����У��Ҹı��ִ����Ⱥ���Ҫ���±������У���ʱ��O(N2), �ռ䣬O(N2)
		/// </summary>
		template<typename T> int LCS(T s) {
			int len = s.size();
			vector<vector<int>> dp = vector<vector<int>>(len, vector<int>(len));
			
			//�߽��ʼ��,�Խ��ߵĻ��ĳ��ȶ�Ϊ1
			for (int i = 0; i < len; ++i) {
				dp[i][i] = 1;
			}

			int max = -1;
			//״̬ת��
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
		/// ��������������һ�������޻�ͼ�����·����������һ��
		///	˼·: ��ȡ�ؼ��֣� �����޻�ͼ�� ·�������
		///		 ���������Ҫ��¼ÿ���㵽�յ��Ȩֵ�ͣ��ұ���õ�����һ��·��
		/// 
		/// </summary>
		template<typename T> int DAG(T s) {
			if (dp[i] > 0) return dp[i];    //�����ָõ���ֵ�����Ƴ��ݹ鷵�ظ�ֵ

			for (int j = 0; j < n; ++j) {   
				if (G[i][j] != 0) {           //G[][]Ϊ�ڽӾ��� 
					int temp = DAG(i) + Gp[i][j]);    //���㵱ǰ�㵽������һ���������ֵ

					if (temp > dp[i]) {
						dp[i] = temp;           //��ֵ�󣬸���dp�͵�ǰ����·��
						choice[i] = j;
					}
				}
			}
			return dp[i];
		}

		/// <summary>
		/// ���⣺��n����Ʒ��ÿ����Ʒ��w[i], �۸�Ϊc[i]��������һ������Ϊv�ı����������ѡȡ��Ʒ���뱳����ʹ�ñ�������Ʒ���ܼ�ֵ�������ÿ����Ʒ��ֻ��һ����
		/// ˼·����ȡ�ؼ��֣�ÿ����Ʒֻ��һ���� �ܼ�ֵ���
		///		 ͨ�����������Ҫ���ϳ��Է���Ʒ����Ȼ��ͣ�������ٽ�ֵ��ʹ��ֵ���Դﵽ���Ϊ��ʡȥ�ظ��ļ��㣬����Ҫ��¼��ÿ�������µļ�ֵ�͡�
		///		 ��ʱ���ǿ��Է��֣��������ǲ���һ���������˵����ǰ�������ǵ�ǰ�����������ô��ǰ�ܼ�ֵ��Ϊ���ֵ��������������˵����ǰ������û��������������£��ܼ�ֵ��Ϊ���
		///      �����ǿ���������ʾ״̬���̣�dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - w[i]] + c[i])
		/// ���Ӷȣ�����Ҫ�����������飬��ʱ�临�Ӷ�O(NM), �ռ临�Ӷȣ�#1, O(NM), #2, O(N)
		/// </summary>
		template<typename T1, typename T2> T2 bag_01(int n, vector<T1> w, vector<T2> c, T1 V) {
			//vector<vector<T1>> dp = vector<vector<int>>(n, vector<T1>(V+1));
			//
			////�߽��ʼ��
			//dp[0][w[0]] = c[0];

			//T2 max_val = c[0];
			////״̬����
			//for (int i = 1; i < n; ++i) {
			//	for (int v = w[i]; v <= V; ++v) {
			//		dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - w[i]] + c[i]);

			//		max_val = max(max_val, dp[i][v]);
			//	}
			//}

			//ʹ�ù�������(����)
			vector<T1> dp(V + 1);
			T2 max_val = c[0];
			//״̬����
			for (int i = 0; i < n; ++i) {
				for (int v = V; v >= w[i]; --v) {
					dp[v] = max(dp[v], dp[v - w[i]] + c[i]);
					max_val = max(max_val, dp[v]);
				}
			}
			
			return max_val;
		}

		/// <summary>
		/// ��ȫ������01�������ƣ����ǲ�ͬ��������һ����Ʒ�����ж����
		/// �ʵ����Ǿ����ŵ�i����Ʒʱ�����ǿ��Լ����������Ʒ�����Բ��ÿ���֮ǰ�����
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

			//ʹ�ù�������(����)
			//vector<T1> dp(V + 1);
			//T2 max_val = c[0];
			////״̬����
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