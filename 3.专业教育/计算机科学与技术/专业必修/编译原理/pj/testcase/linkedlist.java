class LinkedList{
    public static void main(String[] a){
	System.out.println(new LL().Start());
    }
}

class Element {
    int Age ;          
    int Salary ;
    boolean Married ;

    // Initialize some class variables
    public boolean Init(int v_Age, int v_Salary, boolean v_Married){
	Age = v_Age ;
	Salary = v_Salary ;
	Married = v_Married ;
	return true ;
    }

    public int GetAge(){
	return Age ;
    }
    
    public int GetSalary(){
	return Salary ;
    }

    public boolean GetMarried(){
	return Married ;
    }

    // This method returns true if the object "other"
    // has the same values for age, salary and 
    public boolean Equal(Element other){
	boolean ret_val ;
	int aux01 ;
	int aux02 ;
	int nt ;
	ret_val = true ;

	aux01 = other.GetAge();
	if (!this.Compare(aux01,Age)) ret_val = false ;
	else { 
	    aux02 = other.GetSalary();
	    if (!this.Compare(aux02,Salary)) ret_val = false ;
	    else 
		if (Married) 
		    if (!other.GetMarried()) ret_val = false;
		    else nt = 0 ;
		else
		    if (other.GetMarried()) ret_val = false;
		    else nt = 0 ;
	}

	return ret_val ;
    }

    // This method compares two integers and
    // returns true if they are equal and false
    // otherwise
    public boolean Compare(int num1 , int num2){
	boolean retval ;
	int aux02 ;
	retval = false ;
	aux02 = num2 + 1 ;
	if (num1 < num2) retval = false ;
	else if (!(num1 < aux02)) retval = false ;
	else retval = true ;
	return retval ;
    }

}

class List{
    Element elem ;
    List next ;
    boolean end ;

    // Initialize the node list as the last node
    public boolean Init(){
	end = true ;
	return true ;
    }

    // Initialize the values of a new node
    public boolean InitNew(Element v_elem, List v_next, boolean v_end){
	end = v_end ;
	elem = v_elem ;
	next = v_next ;
	return true ;
    }
    
    // Insert a new node at the beginning of the list
    public List Insert(Element new_elem){
	boolean ret_val ;
	List aux03 ;
	List aux02 ;
	aux03 = this ;
	aux02 = new List();
	ret_val = aux02.InitNew(new_elem,aux03,false);
	return aux02 ;
    }
    
    
    // Update the the pointer to the next node
    public boolean SetNext(List v_next){
	next = v_next ;
	return true ;
    }
    
    // Delete an element e from the list
    public List Delete(Element e){
	List my_head ;
	boolean ret_val ;
	boolean aux05;
	List aux01 ;
	List prev ;
	boolean var_end ;
	Element var_elem ;
	int aux04 ;
	int nt ;


	my_head = this ;
	ret_val = false ;
	aux04 = 0 - 1 ;
	aux01 = this ;
	prev = this ;
	var_end = end;
	var_elem = elem ;
	while ((!var_end) && (!ret_val)){
	    if (e.Equal(var_elem)){
		ret_val = true ;
		if (aux04 < 0) { 
		    // delete first element
		    my_head = aux01.GetNext() ;
		} 
		else{ // delete a non first element
		    System.out.println(0-555);
		    aux05 = prev.SetNext(aux01.GetNext());
		    System.out.println(0-555);
		    
		}
	    } else nt = 0 ;
	    if (!ret_val){
		prev = aux01 ;
		aux01 = aux01.GetNext() ;
		var_end = aux01.GetEnd();
		var_elem = aux01.GetElem();
		aux04 = 1 ; 
	    } else nt = 0 ;
	}
	return my_head ;
    }
    
    
    // Search for an element e on the list
    public int Search(Element e){
	int int_ret_val ;
	List aux01 ;
	Element var_elem ;
	boolean var_end ;
	int nt ;

	int_ret_val = 0 ;
	aux01 = this ;
	var_end = end;
	var_elem = elem ;
	while (!var_end){
	    if (e.Equal(var_elem)){
		int_ret_val = 1 ;
	    }
	    else nt = 0 ;
	    aux01 = aux01.GetNext() ;
	    var_end = aux01.GetEnd();
	    var_elem = aux01.GetElem();
	}
	return int_ret_val ;
    }
    
    public boolean GetEnd(){
	return end ;
    }
    
    public Element GetElem(){
	return elem ;
    }
    
    public List GetNext(){
	return next ;
    }
    
    
    // Print the linked list
    public boolean Print(){
	List aux01 ;
	boolean var_end ;
	Element  var_elem ;

	aux01 = this ;
	var_end = end ;
	var_elem = elem ;
	while (!var_end){
	    System.out.println(var_elem.GetAge());
	    aux01 = aux01.GetNext() ;
	    var_end = aux01.GetEnd();
	    var_elem = aux01.GetElem();
	}

	return true ;
    }
}
    

// this class invokes the methods to insert, delete,
// search and print the linked list
class LL{

    public int Start(){

	List head ;
	List last_elem ;
	boolean aux01 ;
	Element el01 ;
	Element el02 ;
	Element el03 ;

	last_elem = new List();
	aux01 = last_elem.Init();
	head = last_elem ;
	aux01 = head.Init();
	aux01 = head.Print();

	// inserting first element
	el01 = new Element();
	aux01 = el01.Init(25,37000,false);
	head = head.Insert(el01);
	aux01 = head.Print();
	System.out.println(10000000);
	// inserting second  element
	el01 = new Element();
	aux01 = el01.Init(39,42000,true);
	el02 = el01 ;
	head = head.Insert(el01);
	aux01 = head.Print();
	System.out.println(10000000);
	// inserting third element
	el01 = new Element();
	aux01 = el01.Init(22,34000,false);
	head = head.Insert(el01);
	aux01 = head.Print();
	el03 = new Element();
	aux01 = el03.Init(27,34000,false);
	System.out.println(head.Search(el02));
	System.out.println(head.Search(el03));
	System.out.println(10000000);
	// inserting fourth element
	el01 = new Element();
	aux01 = el01.Init(28,35000,false);
	head = head.Insert(el01);
	aux01 = head.Print();
	System.out.println(2220000);

	head = head.Delete(el02);
	aux01 = head.Print();
	System.out.println(33300000);


	head = head.Delete(el01);
	aux01 = head.Print();
	System.out.println(44440000);
	
	return 0 ;
	
	
    }
    
}
