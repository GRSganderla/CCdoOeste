<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Produto</title>

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
				<li><a class="button" href="index.jsp"
					style="margin-right: 5px;">Nota de Venda</a></li>
				<li><a class="button" href="notaCompra.jsp"
					style="margin-right: 5px;">Nota de Compra</a></li>
				<li><a class="button" href="" style="margin-right: 5px;">Produto</a></li>
				<li><a class="button" href="chat.jsp" style="margin-right: 5px;">Chat</a></li>
				<li><a class="button" href="consultaNota.jsp">Consulta</a></li>
			</ul>
		</div>
	</div>
	<form action="Produto" method="post">
		<h1 class="text-center">Produto</h1>

		<div class="grid-container">

			<div class="grid-x grid-padding-x">

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label">Cod. Produto</span> <input
							class="input-group-field" type="text" name="codProd" value="${codProd}">
					</div>
				</div>

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label">Cod. Barras</span> <input
							class="input-group-field" type="text" name="codBarras" value="${codBarras}" readonly>
					</div>
				</div>

				<div class="medium-12 cell">
					<div class="input-group">
						<span class="input-group-label">Nome do Produto</span> <input
							class="input-group-field" type="text" name="nomeProd"
							value="${nomeProd}"readonly>
					</div>
				</div>

				<div class="medium-12 cell">
					<div class="input-group">
						<span class="input-group-label">Fornecedor Principal</span> <input
							class="input-group-field" type="text" name="forPrincipal"
							value="${fornecedor}"readonly>
					</div>
				</div>

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label">Preço Custo Atual</span> <input
							class="input-group-field" type="text" name="prAtual"
							value="${prAtual}" readonly>
					</div>
				</div>

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label">Preço de Venda</span> <input
							class="input-group-field" type="number" name="prVenda"
							value="${prVenda}" readonly>
					</div>
				</div>

				<div class="medium-6 cell">
					<div class="input-group">
						<span class="input-group-label">Qtd Atual em Estoque</span> <input
							class="input-group-field" type="number" value="${qtdAtual}"
							readonly>
					</div>
				</div>

			</div>

			<input type="submit" class="button" value="Consultar"></input> <input
				type="reset" class="button float-right" value="Cancelar"></input>

		</div>
	</form>

	<script src="./js/vendor/jquery.js" type="text/javascript"></script>
	<script src="./js/vendor/foundation.js" type="text/javascript"></script>
	<script src="./js/app.js" type="text/javascript"></script>
	<script src="./js/auxiliar.js" type="text/javascript"></script>

</body>
</html>