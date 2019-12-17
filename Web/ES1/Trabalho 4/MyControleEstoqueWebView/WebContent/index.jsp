<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Nota de Venda</title>

<link rel="stylesheet" type="text/css" href="./css/foundation.css" />
<script type="text/javascript">
var Msg ='<%=session.getAttribute("Alert")%>';
    if (Msg != "No" && Msg != "null") {
		 function alertName(){
		 	alert(Msg);
		 	} 
 		}
 </script> 
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
				<li><a class="button" href="" style="margin-right: 5px;">Nota
						de Venda</a></li>
				<li><a class="button" href="notaCompra.jsp"
					style="margin-right: 5px;">Nota de Compra</a></li>
				<li><a class="button" href="produto.jsp"
					style="margin-right: 5px;">Produto</a></li>
				<li><a class="button" href="chat.jsp" style="margin-right: 5px;">Chat</a></li>
				<li><a class="button" href="consultaNota.jsp">Consulta</a></li>

			</ul>
		</div>
	</div>

	<form action="notaVenda" method="post">
		<h1 class="text-center">Nota de Venda</h1>

		<div class="grid-container">

			<div class="grid-x grid-padding-x">

				<div class="medium-4 cell">
					<div class="input-group">
						<span class="input-group-label"> Numero da Nota</span> <input
							class="input-group-field" type="text" name="numNota">
					</div>
				</div>

				<div class="medium-4 cell">
					<div class="input-group">
						<span class="input-group-label">Data</span> <input
							class="input-group-field" type="date" name="data">
					</div>
				</div>

				<div class="medium-4 cell">
					<div class="input-group">
						<span class="input-group-label">Cliente</span> <input
							class="input-group-field" type="text" name="cliente">
					</div>
				</div>

				<div class="medium-12 cell">
					<div class="input-group">
						<span class="input-group-label">Cod</span> <input id="cod"
							class="input-group-field" type="text"></input> <span
							class="input-group-label">Produto</span> <input id="prod"
							class="input-group-field" type="text"></input> <span
							class="input-group-label">Qtd</span> <input id="qtd"
							class="input-group-field" type="number"></input> <span
							class="input-group-label">Preco</span> <input id="preco"
							class="input-group-field" type="number" step="0.01"></input>

						<div class="input-group-button">
							<button class="button" type="button" onclick="addItem()"
								id="botao_tabela">+</button>
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

					</tbody>
				</table>

			</div>

			<div class="row">
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Total Nota</span> <input
							id="totNota" class="input-group-field" type="number"
							name="totNota" step="0.01" readonly>
					</div>
				</div>
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Desconto</span> <input id="descTot"
							class="input-group-field" type="number" name="descTot"
							step="0.01">
					</div>
				</div>
				<div class="columns uncentered">
					<div class="input-group">
						<span class="input-group-label">Valor Liquido</span> <input
							id="valorLiq" class="input-group-field" type="number"
							name="valorLiq" step="0.01" readonly>
					</div>
				</div>
			</div>

			<input type="submit" class="button" value="Registrar" onclick=clear()></input>
			<input type="reset" class="button float-right" value="Cancelar"></input>

		</div>
	</form>

	<script src="./js/vendor/jquery.js" type="text/javascript"></script>
	<script src="./js/vendor/foundation.js" type="text/javascript"></script>
	<script src="./js/app.js" type="text/javascript"></script>
	<script src="./js/auxiliar.js" type="text/javascript"></script>

</body>
</html>