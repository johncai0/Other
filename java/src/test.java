class test {
	public static void main(String[] args) {
		//int b[] = {1,4,3,2,9,6,7,5};
		int b[] = {9,3,7,2,5,1};
		BubbleSort(b);
		//int index = search(b,7);
		//System.out.println("index = " + index);
	}
	public static int search(int a[], int b) {
		int min = 0;
		int max = a.length-1;
		int mid = (min + max)>>1;
		while (max >= min) {
			//System.out.println("max = " + max + " min = " + min + " mid = " + mid + " a[mid] = " + a[mid]);
			if (a[mid] < b) {
				min = mid+1;
				mid = (min+max)>>1;
			} else if (a[mid] > b) {
				max = mid-1;
				mid = (min+max)>>1;
			} else {
				return mid;
			}
		}
		return -1;
	}
	public static void BubbleSort(int a[]) {
		for (int i = 0; i<a.length; i++) {
			for (int j = i; j<a.length; j++) {
				if (a[i] > a[j]) {
					int tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
				}
				System.out.print("sortH:["+i+"]["+j+"]\t");
				prt(a);
			}
		}
	}
	public static void prt(int a[]) {
		for (int i = 0; i<a.length; i++)
                        System.out.print("|" + a[i] );
                System.out.println("|");
	}
}
