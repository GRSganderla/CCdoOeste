<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<style>
table, th, td {
  border: 1px solid black;
  border-collapse: collapse;
}
td {

  text-align: center;
}

th, td{

  padding: 5px;
}
</style>
<meta charset="ISO-8859-1">
<title>Insert title here</title>
<link rel="stylesheet" href="src/foundation.css" />
</head>
<body>
	
	<form action="Menu.jsp" method="post">
	
		<h4> Cod Paciente:  		</h4><h4> Nome Paciente:  			</h4><h4> CPF:</h4>
		
		<h4> Endereço : 			</h4><h4> Cep: 			</h4><h4> Rua: 			</h4><h4> NúmeroCasa: 		</h4><h4> Bairro:</h4>
			
		<h4> Cidade: 		</h4><h4> UF:  		</h4><h4> Complemento:</h4>  
		
		<h4> Telefone:  </h4>
		
		<h4> Email: </h4>
		
		<h4> Data Nascimento : 			</h4><h4> Sexo: </h4> 
		
		<h4> TipoSanguíneo:  </h4>
		
		<h2> Consultas Realizadas:</h2>
		 <table style="stack">
		  <tr>
		    <th>   DataConsulta   </th>
		    <th>   TipoConsulta   </th>
		    <th>   CidConsulta   </th>
		    <th>   Nome Medico   </th>
		    <th>   CRM Médico   </th>
		  </tr>
		  <tr>
		    <td>----------</td>		    
		    <td>----------</td>
		    <td>----------</td>
		    <td>----------</td>
		    <td>----------</td>
		  </tr>
		</table> 
		
		<h2> Exames Realizados:</h2>
		<table style="stack">
			<tr>
				<th>   DataExame   </th>
				<th>   TipoExame   </th>
				<th>   Resultado   </th>
			</tr>
			<tr>
			    <td>----------</td>
			    <td>----------</td>
			    <td>----------</td>
			</tr>
		</table>
						
		<h2> Remédios Prescritos:</h2>  
		<table style="stack">
			<tr>
				<th>   Data   </th>
				<th>   Remédio   </th>
				<th>   Posologia   </th>
			</tr>
			<tr>
			   	<td>----------</td>
			   	<td>----------</td>
				<td>----------</td>
			</tr>
		</table>
		<br>
		<input type="submit" value="Menu"/>
		</form>
</body>
</html>