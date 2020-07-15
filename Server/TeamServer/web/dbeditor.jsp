<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv='Content-Type' content='text/html' charset='UTF-8'/>
    <title>DB Editor</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/db_editor.css">
    <script>
        document.contextPath = "${pageContext.request.contextPath}";
    </script>
    <script type="text/javascript" src="${pageContext.request.contextPath}/js/db_editor.js"></script>
</head>
<header>

</header>
<body>
<div class="main">
    <div class="create_user" align="center">
        <div  align="center">
            <span class="create_user_header1">Team</span> <span class="create_user_header2">Work</span><br>
            <h1 class="create_user">Создание пользователя</h1><br>

            <div align="left" class="create_user_subtitle">
                <span class="create_user_subtitle">Имя</span>
            </div>.
            <input class="create_user" type="text" name="name" id="name" autocomplete="off"><br>

            <div align="left" class="create_user_subtitle">
                <span class="create_user_subtitle">Фамилия</span>
            </div>
            <input class="create_user" type="text" name="lastname" id="lastname" autocomplete="off"><br>

            <div align="left" class="create_user_subtitle">
                <span class="create_user_subtitle">Email</span>
            </div>
            <input class="create_user" type="text" name="email" id="email" autocomplete="off"><br>

            <div align="left" class="create_user_subtitle">
                <span class="create_user_subtitle">Пароль</span>
            </div>
            <input class="create_user" type="password" name="passsword" id="password" autocomplete="off">
            <button class="create_user_create" onclick="createUser()">Создать</button>
        </div>
    </div>
</div>
</body>
</html>