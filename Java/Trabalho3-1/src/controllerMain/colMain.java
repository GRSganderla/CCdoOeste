package controllerMain;

import Infra.SQLconnection;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Scanner;

public class colMain {

	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		  
		  Connection conn;
		  Scanner scan = new Scanner(System.in);
		  Integer opcao, i = 1, escolha = 1;
		  ArrayList<String> nomes = null;
		  conn = SQLconnection.getConnection("root", "1702");
		  
		  try {
			nomes = SQLconnection.getCliente(conn);
		  } catch (Exception e1) {
			  
			e1.printStackTrace();
		  }
		  
		  while(true) {
			  i = 1;
			  escolha = 1;
			  System.out.println("Escolha o Cliente: ");
			  for(String a : nomes) {
				  System.out.println(i++ + " -> " +  a);
			  }
			  
			  System.out.println("0 -> Sair");
			  System.out.print("Escolha: ");
			  opcao = scan.nextInt();
			  scan.nextLine();
			  
			  if(opcao <= 0) {
				  
				  break;
			  }
			  else if(opcao <= i){
				  
				  try {
					Integer conta = SQLconnection.getConta(conn, opcao);
					
					while(escolha != 0) {
						System.out.println("Indique a consulta a ser feital");
						System.out.println("1 -> Imprimir extrato Conta-Corrente");
						System.out.println("2 -> Imprimir Lista de Investimentos");
						System.out.println("0 -> Sair");
						System.out.print("Escolha: ");
						escolha = scan.nextInt();
						scan.nextLine();
						if(escolha == 1) SQLconnection.getExtrato(conn, conta);
						else if(escolha == 2) SQLconnection.getListaInv(conn, conta);
					}
					} catch (Exception e) {
						
						e.printStackTrace();
					}
			  }
		  }
			  
		  conn.close();
		  scan.close();
	  }

}
