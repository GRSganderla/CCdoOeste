<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" type="text/css" href="css/foundation.css">
<title>Extrato</title>
</head>
<body>

 	<div class="top-bar" style="background-color: orange;">
  		<div class="top-bar-left">
 
 		</div>
	  	<div class="top-bar-right">
		    <ul class="menu">
		      <li><a class="button" href="index.jsp">Voltar</a></li>
		    </ul>
		 </div>
	</div>

	<div class="grid-container">

		<div class="grid-x grid-padding-x">

			<div class="medium-6 cell">
				<label>Cliente: <input type="text" value="${cliente}"
					readonly>
				</label>
			</div>

			<div class="medium-6 cell">
				<label>CPF/CNPJ: <input type="text" value="${cpf_cnpj}"
					readonly>
				</label>
			</div>

		</div>

		<table>
			<thead>

				<tr>
					<th>Data</th>
					<th>Cod/</th>
					<th>Motivo da transação</th>
					<th>Valor da transação</th>
				</tr>
			</thead>
			<tbody>

				<c:forEach items="${tabela}" var="index">
				
					<tr>
						<td><c:out value="${index[0]}" /></td>
						<td><c:out value="${index[1]}" /></td>
						<td><c:out value="${index[2]}" /></td>
						<td><c:out value="${index[3]}" /></td>

					</tr>

				</c:forEach>
			</tbody>

		</table>

		<div class="grid-x grid-padding-x">

			<div class="medium-6 cell">
				<label>Saldo atual: R$ <input type="number" value="${saldo}"
					readonly>
				</label>
			</div>

		</div>

	</div>

</body>
</html>