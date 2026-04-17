using System;
using System.Linq;//リストの使用
using System.Collections.Generic;
using System.Text;//テキストの高速出力に必要
class Program
{
	static void Main()
	{
		string[] input = Console.ReadLine().Split(' ');
		int n = int.Parse(input[0]);
		int k = int.Parse(input[1]);
		
		int count = 0;
		
		if(n != 0 && k != 0){
			count = n-k+1;
		}
	
		Console.WriteLine(count);
	}
}