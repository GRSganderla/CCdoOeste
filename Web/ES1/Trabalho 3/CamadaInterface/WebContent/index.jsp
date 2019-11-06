<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>


<!DOCTYPE html>
<html>
   <head>
      <meta charset="ISO-8859-1">
      <style>
      	  b { 
		  font-weight: bold;
		  }
     	  input[type=submit] {
		  background-color: #4CAF50;
		  border: none;
		  color: white;
		  padding: 16px 32px;
		  text-decoration: none;
		  margin: 4px 2px;
		  cursor: pointer;
		  border-radius: 8px;
		 }		
      	 input[type=text] {
		  width: 80%;
		  padding: 12px 20px;
		  margin: 8px 0;
		  box-sizing: border-box;
		  border-radius: 4px;
		 }
      	 fieldset {
      	 	background-color: #e6e6e6;
      	 	 display: block;
			  margin-left: 2px;
			  margin-right: 2px;
			  padding-top: 0.35em;
			  padding-bottom: 0.625em;
  			padding-left: 0.75em;
 			padding-right: 0.75em;
  			border: 2px groove (internal value);
      	 }
      	 body {
      	 	background-color: #80d4ff;
      	 }
         .site div{
         width: 700px;
         height: 700px;
         position: absolute;
         left: 50%;
         top: 50%;
         transform: translate(-50%, -50%);
         }
         .header div{
         width:100px;
         height:100px;
         }
         .conteudo div{
         width:1100px;
         height:500px;
         } 
         .footer div{
         width:1000px;
         height:100px;
         }
         .conteudo-left div{
         width:600px;
         height:100px;
         float:left;
         }
         .conteudo-right{
         width:500px;
         height:100px;
         float:left;
         }
         .conteudo-left-left{
         width: 300px;
         height: 100px;
         float:left;
         }
         .conteudo-right-right{
         width: 300px;
         height: 100px;
         float:left;
         }
         h2{
         	text-align: center;
  			text-shadow: 2px 2px 2px gray;
         }
      </style>
      <title>Endereço</title>
   </head>
   <body>
      <div class="site">
         <div class="header"></div>
         <div class="conteudo">
            <fieldset>
               <h2>Consultar Endereço</h2>
               <form action="ObterPorCEPServlet" method = "post">
                  <h3> Consultar por CEP: <br>
                  <input type="text" id="PorCEP" name="PorCEP"/>
                  <input type="submit" value="Consultar"/></h3>
               </form>
               <form action="ObterPorIDServlet" method = "post">
                  <h3> Consultar por ID: <input type="text" id="PorID" name="PorID"/>
                  <input type="submit" value="Consultar"/></h3>
               </form>
               <form action="ObterEndExtServlet" method = "post">
                  <h3> Consultar Endereço Externo: <input type="text" id="EndExt" name="EndExt"/>
                  <input type="submit" value="Consultar"/></h3>
               </form>
               <form action="ObterCidadeServlet" method = "post">
                  <h3> Consultar Cidade: <input type="text" id="cidade" name="cidade"/>
                  <input type="submit" value="Consultar"/></h3>
               </form>
            </fieldset>
         </div>
      </div>
   </body>
</html>

