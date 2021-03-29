#include <iostream>
#include <vector>

using std::vector;
namespace N {
	class sort {
	public:

		/// <summary>
		/// ����������
		/// </summary>
		template<typename T> void swap(T& a, T& b) {
			T temp = a;
			a = b;
			b = temp;
		};

		/// <summary>
		/// ð�����򣺱Ƚ�ÿ����������С�����֣�ͨ�������������ϰ���С�����Ƶ���������ˣ�Ȼ���ͷ��ʼ�ظ�Ѱ�ҵڶ�����С����
		/// ��һ������Ҫ N �αȽϣ�Ȼ����Ѱ�ҵģ���Ҫ���ظ� N-1 �Σ� �����ǿ���������forѭ��,�ڶ���forѭ�����ö�̬�߽磨������Ҫ�ٱȽ������С������
		/// ���Ӷȣ�ʱ��: O(N*N),�������������˳����������Ҫ��˳���෴; �ռ�:O(1), û�ж���Ŀռ䣬����һ����ʱ���������Ժ��Բ���
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
		/// ѡ�������ҳ���������С������Ȼ���䰴������˳�����ָ����λ��
		/// ������Ҫ���ϱ�������������Ѱ����С�����������鳤��ΪN����Ҫ���� (N-1)+(N-2).....+1
		/// ���Ӷȣ� ʱ��:O((N*N)/2), �ռ䣺O(1)
		/// �����ð����˵������Ҫÿ�αȽ϶�ȥ����λ�á����ԱȽϱ���
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
		/// ��������: ָ��һ������ļ��ϣ����ޣ������������һ�����ü��ϣ���Ȼ����֮��Ϊ���������ü��Ͻ��жԱȣ��ٽ��в���Ĳ���
		/// ��ð�ݺ�ѡ�����ƣ�����Ҫ�������Σ�
		/// ���Ӷȣ�ʱ��: O((N*N)/2), �ռ䣺O(1)
		/// ��������ð�ݺ�ѡ������һЩ������������һЩ�ظ��ıȽϲ���
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
		/// ������: ������ȫ����������������������ԣ����ϵ��£������ң��� �������е�Ԫ����֮��Ӧ�ҳ���С���ֵ��
		/// ʱ�临�Ӷȣ���������Ҫ���ϵ����ѣ��ҵ���һ�ζ�����ʱ��Ϊlogn, ����������Ҫn������ʱ����ҪO(n*logn)��
		/// </summary>
		template<typename T> void HeapSort(vector<T>& v, int i) {
			buildheap(v, 0);
			int len = v.size();
			int lastnode = len - 1;

			//Ϊȡ���������������һ����㻥��λ�ã�Ȼ�����������ʣ�������heapify��Ȼ���ظ����ϲ���
			for (i = lastnode; i > 0; --i) {
				swap(v[0], v[i]);
				Heapify(v, i, 0);
			}
		}

		/// <summary>
		/// �鲢���򣺽��������в��ϻ��ֵ���С��Ԫ����������Ȼ���ٲ�������ԭ���Ĵ������������ֱ�ӵ�˼��ľ��ǻ��õ��ݹ顣
		/// ���Ӷȣ�����Ҫ���ݹ飬�ʵݹ��ʱ��ʱlogn, ��ÿ���ʱ��Ϊn�� ����ʱ�临�Ӷ�ΪO(nlogn)
		/// </summary>
		template<typename T> void Groupsort(vector<T>& t, int L, int R) {

			if (L == R) return;
			int mid = (L + R) / 2;
			Groupsort(t, L, mid);
			Groupsort(t, mid + 1, R);

			_GroupSort(t, L, mid+1, R);
		}

		/// <summary>
		/// ��������ѡһ����׼��Ȼ��Աȣ�С�ķ�һ�ߣ���ķ�һ�ߣ�Ȼ���ٿ�������С��һ�Ѻʹ��һ�ѡ�
		/// ��ʾ����ѡ��������ĳ��ֵ����׼ʱ�����ǿ��Խ�����ȡ�����������Ǻ�����ԭ�����������������
		/// ���Ӷȣ������õ��ݹ飬��ÿ�εݹ鶼Ҫ����n-1�αȽϣ��ʸ��Ӷ�ΪO(nlogn)
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
		//�������Ӷ��ϣ����ϵؽ�����
		template<typename T> void Heapify(vector<T>& v, int n, int i) {
			if (i > n) return;  //Ҷ�ڵ����в�����������

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

		//�����ѣ� �Ӷ������һ�����ڵ㿪ʼ����
		template<typename T> void buildheap(vector<T>& v, int i) {
			int len = v.size();
			int lastnode = len - 1;
			int parent_lastnode = (lastnode - 1)/2;

			for (i = parent_lastnode; i >= 0; --i) {
				Heapify(v, len, i);
			}
		}

		//����������Ĳ��ֽ��кϲ�
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

