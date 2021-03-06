module adder_half(output S, C, input A, B);
	xor sum(S,A,B);
	and carry(C,A,B);
endmodule

module adder_full(output S, Cout, input A,B,Cin);
	wire s1, c1, c2;
	adder_half ha1(s1,c1, A ,B  ),
		ha2(S ,c2, s1,Cin);
	or carry(Cout, c1,c2);
endmodule

module adder_4b(output [3:0]S, output Cout, input [3:0]A, B, input Cin);
	wire c1, c2, c3;

	adder_full fa1(S[0], c1,   A[0], B[0], Cin),
		fa2(S[1], c2,   A[1], B[1], c1),
		fa3(S[2], c3,   A[2], B[2], c2),
		fa4(S[3], Cout, A[3], B[3], c3);
endmodule

module adder_16b(output [15:0]S, output Cout, input [15:0] A, B, input Cin);
	wire c1, c2, c3;
	adder_4b a1(S[ 3: 0], c1,   A[ 3: 0], B[ 3: 0], Cin),
	         a2(S[ 7: 4], c2,   A[ 7: 4], B[ 7: 4], c1),
	         a3(S[11: 8], c3,   A[11: 8], B[11: 8], c2),
	         a4(S[15:12], Cout, A[15:12], B[15:12], c3);
endmodule
