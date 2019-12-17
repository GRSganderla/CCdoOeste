<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Consulta de nota</title>

<link rel="stylesheet" type="text/css" href="./css/foundation.css" />

</head>
<body>

	<div class="title-bar" data-responsive-toggle="responsive-menu"
		data-hide-for="medium">
		<button class="menu-icon" type="button" data-toggle="responsive-menu"></button>
		<div class="title-bar-title">Menu</div>
	</div>

	<div class="top-bar" id="responsive-menu">
		<div class="top-bar-right">
			<ul class="dropdown menu" data-dropdown-menu>
				<li><a class="button" href="" style="margin-right: 5px;">Consulta
						de nota</a></li>
				<li><a class="button" href="notaCompra.jsp"
					style="margin-right: 5px;">Nota de Compra</a></li>
				<li><a class="button" href="produto.jsp"
					style="margin-right: 5px;">Produto</a></li>
				<li><a class="button" href="chat.jsp" style="margin-right: 5px;">Chat</a></li>
				<li><a class="button" href="">Consulta</a></li>
			</ul>
		</div>
	</div>

	<form action="consultaNota" method="post">
		<h1 class="text-center">Consultar Nota</h1>

		<div class="grid-container">

			<div class="grid-x grid-padding-x">

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label"> Numero da Nota</span> <input
							class="input-group-field" type="text" name="numNota"
							value="${numNota}">
					</div>
				</div>

				<fieldset class="medium-6 cell">
					<legend>Tipo de nota</legend>

					<input type="radio" name="tipo" value="Venda" id="venda" required>

					<label for="venda">Venda</label> <input type="radio" name="tipo"
						value="Compra" id="compra"> <label for="compra">Compra</label>
				</fieldset>

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label">Data</span> <input
							class="input-group-field" type="date" name="data" value="${data}" readonly>
					</div>
				</div>

 				<div class="medium-12 cell"> 
					<div class="input-group"> 
 						<span class="input-group-label">Cliente</span> <input
 							class="input-group-field" type="text" name="cliente" value="${cliente}" readonly>
 					</div>
 				</div>
			</div>
	
			<table id="table centered" class="unstriped">
					<tbody id="tbody">
						<tr>
							<th>Cod</th>
							<th>Produto</th>
							<th>Qtde</th>
							<th>Preco</th>
							<th>Total</th>
						</tr>
						<c:forEach items="${tabela}" var="index">
					
						<tr>
							<td><c:out value="${index[0]}" /></td>
							<td><c:out value="${index[1]}" /></td>
							<td><c:out value="${index[2]}" /></td>
							<td><c:out value="${index[3]}" /></td>
							<td><c:out value="${index[4]}" /></td>
	
						</tr>
	
					</c:forEach>

					</tbody>
			</table>

			<div class="row">
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Total Nota</span> <input
							id="totNota" class="input-group-field" type="number"
							name="totNota" step="0.01" value="${totNota}" readonly>
					</div>
				</div>
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Desconto</span> <input id="descTot"
							class="input-group-field" type="number" name="descTot"
							step="0.01" value="${descTot}" readonly>
					</div>
				</div>
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Valor Liquido</span> <input
							id="valorLiq" class="input-group-field" type="number"
							name="valorLiq" step="0.01" value="${valorLiq}" readonly>
					</div>
				</div>
			</div>
			
			<input type="submit" class="button" value="Consultar" onclick=clear()></input>
			<input type="reset" class="button float-right" value="Cancelar"></input>
		</div>
	</form>


	<script src="./js/vendor/jquery.js" type="text/javascript"></script>
	<script src="./js/vendor/foundation.js" type="text/javascript"></script>
	<script src="./js/app.js" type="text/javascript"></script>
	<script src="./js/auxiliar.js" type="text/javascript"></script>


</body>
</html>