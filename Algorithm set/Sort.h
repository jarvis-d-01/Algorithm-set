#include <iostream>
#include <vector>

using std::vector;
namespace N {
	class sort {
	public:

		/// <summary>
		/// 交换两个数
		/// </summary>
		template<typename T> void swap(T& a, T& b) {
			T temp = a;
			a = b;
			b = temp;
		};

		/// <summary>
		/// 冒泡排序：比较每个集合内最小的数字，通过两两交换不断把最小的数移到集合最左端，然后从头开始重复寻找第二个最小的数
		/// 第一次排序要 N 次比较，然后再寻找的，需要再重复 N-1 次， 故我们可以用两个for循环,第二个for循环设置动态边界（即不需要再比较左边最小的数）
		/// 复杂度：时间: O(N*N),极端情况，集合顺序正好与需要的顺序相反; 空间:O(1), 没有额外的空间，仅有一个临时变量，可以忽略不计
		/// </summary>
		template<typename T> void Bubblesort(vector<T>& t) {
			int len = t.size();

			for (int i = 0; i < len; ++i) {
				for (int j = len - 1; j > i; --j) {
					if (t[j - 1] > t[j]) {
						swap(t[j - 1], t[j]);
					}
				}
			}
		};

		/// <summary>
		/// 选择排序：找出数组内最小的数，然后将其按照所需顺序放在指定的位置
		/// 我们需要不断遍历整个数组来寻找最小的数，若数组长度为N，则要遍历 (N-1)+(N-2).....+1
		/// 复杂度： 时间:O((N*N)/2), 空间：O(1)
		/// 相较于冒泡来说，不需要每次比较都去交换位置。但仍比较暴力
		/// </summary>
		template<typename T> void Selectionsort(vector<T>& t) {
			int len = t.size();
			int min;
			T val;

			for (int i = 0; i < len - 1; ++i) {
				min = i;
				val = t[i];

				for (int j = i + 1; j < len; ++j) {
					if (val > t[j]) {
						min = j;
						val = t[j];
					}
				}
				swap(t[i], t[min]);
			}
		}

		/// <summary>
		/// 插入排序: 指定一个有序的集合（若无，可以随机放置一个到该集合），然后用之后为排序的数与该集合进行对比，再进行插入的操作
		/// 与冒泡和选择类似，都需要遍历两次，
		/// 复杂度：时间: O((N*N)/2), 空间：O(1)
		/// 这个相较于冒泡和选择，有了一些改良。减少了一些重复的比较操作
		/// </summary>
		template<typename T> void Insertsort(vector<T>& t) {
			int len = t.size();

			for (int i = 1; i < len; ++i) {
				for (int j = i; j > 0; --j) {
					if (t[j - 1] > t[j]) {
						swap(t[j - 1], t[j]);
					}
					else {
						break;
					}
				}
			}

		}

		/// <summary>
		/// 堆排序: 根据完全二叉树结点序列连续的特性（从上到下，从左到右）， 将数组中的元素与之对应找出最小最大值。
		/// 时间复杂度：由于其需要不断调整堆，且调整一次堆所需时间为logn, 故最坏的情况需要n个数据时，需要O(n*logn)。
		/// </summary>
		template<typename T> void HeapSort(vector<T>& v, int i) {
			buildheap(v, 0);
			int len = v.size();
			int lastnode = len - 1;

			//为取出顶，将其与最后一个结点互换位置，然后将它择出，对剩余结点进行heapify，然后重复以上操作
			for (i = lastnode; i > 0; --i) {
				swap(v[0], v[i]);
				Heapify(v, i, 0);
			}
		}

		/// <summary>
		/// 归并排序：将整个序列不断划分到最小单元，进行排序，然后再不断升级原来的大数组进行排序。直接的思想的就是会用到递归。
		/// 复杂度：由于要层层递归，故递归的时间时logn, 且每层的时间为n， 故总时间复杂度为O(nlogn)
		/// </summary>
		template<typename T> void Groupsort(vector<T>& t, int L, int R) {

			if (L == R) return;
			int mid = (L + R) / 2;
			Groupsort(t, L, mid);
			Groupsort(t, mid + 1, R);

			_GroupSort(t, L, mid+1, R);
		}

		/// <summary>
		/// 快速排序：选一个标准，然后对比，小的放一边，大的放一边，然后再快速排序小的一堆和大的一堆。
		/// 提示：当选择数组内某个值当标准时，我们可以将它提取出来利于我们后续对原有数组进行重新排序
		/// 复杂度：由于用到递归，且每次递归都要进行n-1次比较，故复杂度为O(nlogn)
		/// </summary>
		template<typename T> void QuickSort(vector<T>& v, int L, int R) {
			T pivot = v[L];
			int L_pre = L;
			int R_pre = R;

			while (L < R) {
				if (v[R] < pivot) {
					v[L] = v[R];
					--R;
				}

				if (v[L] > pivot) {
					v[R] = v[L];
					++L;
				}
			}

			v[L] = pivot;

			QuickSort(v, L_pre, L);
			QuickSort(v, R, R_pre);
		}

		/// <summary>
		/// 
		/// </summary>
	private:
		//在已有子堆上，不断地建立堆
		template<typename T> void Heapify(vector<T>& v, int n, int i) {
			if (i > n) return;  //叶节点序列不超过结点个数

			int l_node = 2 * i + 1;
			int r_node = 2 * i + 2;
			int max = i;

			if (l_node < n && v[i] < v[l_node]) {
				max = l_node;
			}

			if (r_node < n && v[max] < v[r_node]) {
				max = r_node;
			}

			if (max != i) {
				swap(v[i], v[max]);
				Heapify(v, n, max);
			}
		}

		//构建堆， 从堆中最后一个父节点开始构建
		template<typename T> void buildheap(vector<T>& v, int i) {
			int len = v.size();
			int lastnode = len - 1;
			int parent_lastnode = (lastnode - 1)/2;

			for (i = parent_lastnode; i >= 0; --i) {
				Heapify(v, len, i);
			}
		}

		//对两个有序的部分进行合并
		template<typename T> void _GroupSort(vector<T>& v, int L, int M, int R) {
			int left_size = M - L;
			int right_size = R - M + 1;
			
			vector<T> LeftV(left_size);
			vector<T> RightV(right_size);

			for (int i = L; i < M; ++i) {
				LeftV[i-L] = v[i];
			}

			for (int i = M; i <= R; ++i) {
				RightV[i - M] = v[i];
			}

			int i = 0, j = 0, k = L;

			while (i < left_size && j < right_size) {
				if (LeftV[i] < RightV[j]) {
					v[k++] = LeftV[i++];
				}
				else {
					v[k++] = RightV[j++];
				}
			}

			while (i < left_size)
				v[k++] = LeftV[i++];
			while (j < right_size)
				v[k++] = RightV[j++];
		}
	};
};

