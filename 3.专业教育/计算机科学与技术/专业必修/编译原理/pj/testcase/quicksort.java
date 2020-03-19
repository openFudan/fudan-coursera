class QuickSort{
    public static void main(String[] a){
	System.out.println(new QS().Start(10));
    }
}


// This class contains the array of integers and
// methods to initialize, print and sort the array
// using Quicksort
class QS{
    
    int[] number ;
    int size ;

    // Invoke the Initialization, Sort and Printing
    // Methods
    public int Start(int sz){
	int aux01 ;
	aux01 = this.Init(sz);
	aux01 = this.Print();
	System.out.println(9999);
	aux01 = size - 1 ;
	aux01 = this.Sort(0,aux01);
	aux01 = this.Print();
	return 0 ;
    }

 
    // Sort array of integers using Quicksort method
    public int Sort(int left, int right){
	int v ;
	int i ;
	int j ;
	int nt;
	int t ;
	boolean cont01;
	boolean cont02;
	int aux03 ;
	t = 0 ;
	if (left < right){
	    v = number[right] ;
	    i = left - 1 ;
	    j = right ;
	    cont01 = true ;
	    while (cont01){
		cont02 = true ;
		while (cont02){
		    i = i + 1 ;
		    aux03 = number[i] ;
		    if (!(aux03<v)) cont02 = false ;
		    else cont02 = true ;
		}
		cont02 = true ;
		while (cont02){
		    j = j - 1 ;
		    aux03 = number[j] ;
		    if (!(v < aux03)) cont02 = false ;
		    else cont02 = true ;
		}


		t = number[i] ;
		number[i] = number[j] ;
		number[j] = t ;
		//aux03 = i + 1 ;
		if ( j < (i+1)) cont01 = false ;
		else cont01 = true ;
	    }
	    number[j] = number[i] ;
	    number[i] = number[right] ;
	    number[right] = t ;
	    nt = this.Sort(left,i-1);
	    nt = this.Sort(i+1,right);
	}
	else nt = 0 ;
	return 0 ;
    }

    
    // Print array of integers
    public int Print(){
	int j ;
	j = 0 ;
	while (j < (size)) {
	    System.out.println(number[j]);
	    j = j + 1 ;
	}
	return 0 ;
    }
    

    // Initialize array of integers
    public int Init(int sz){
	size = sz ;
	number = new int[sz] ;
	
	number[0] = 20 ;
	number[1] = 7  ; 
	number[2] = 12 ;
	number[3] = 18 ;
	number[4] = 2  ; 
	number[5] = 11 ;
	number[6] = 6  ; 
	number[7] = 9  ; 
	number[8] = 19 ; 
	number[9] = 5  ;
	
	return 0 ;	
    }

}
