# Adm-Hospitalar
Projeto para a disciplina de Estrutura de Dados Orientada a Objetos.

      Admistrador Hospitalar:
Plataforma médica de gestão desenvolvida em C++ com uma interface funcional projetada no Qt Creator. O sistema foi arquitetado seguindo os princípios da programação orientada a objetos, garantindo uma estrutura organizada, escalável e de fácil manutenção.

A plataforma oferece três tipos de acesso:
- Paciente: permite agendar consultas e cirurgias de forma intuitiva, além de acompanhar os atendimentos. É preciso selecionar o dia antes de pesquisar, para que as consultas e cirurgias apareçam no sistema.
- Médico: facilita a gestão da agenda de consultas e cirurgias, promovendo um atendimento mais eficiente e integrado. Ele também consegue acompanhar suas consultas a partir do dia que deseja verificar.
- Administrador: proporciona controle total sobre o sistema, incluindo o gerenciamento de cadastros de médicos e pacientes, a agenda geral do consultório, e o monitoramento e organização do inventário de itens médicos.

Com a integração do Qt, a interface é visualmente atrativa, entregando uma boa experiência ao usuário. A orientação a objetos traz maior modularidade ao código, permitindo a adição de novas funcionalidades com facilidade, além da formação de heranças entre as classes para que os dados necessários sejam repassados entre elas. Essa estrutura robusta busca otimizar os processos administrativos e clínicos, garantindo uma gestão médica eficiente e simplificada.

Acesso ao banco de dados:

![WhatsApp Image 2025-01-30 at 22 31 30 (1)](https://github.com/user-attachments/assets/9dfbbd7e-dcb5-48a7-b3fd-6748d9d0fca0)

Tela de login:

![WhatsApp Image 2025-01-30 at 22 34 22](https://github.com/user-attachments/assets/46f5192f-1976-4696-a02c-5774aaa9e1aa)

Tela de Início - Médico:

![WhatsApp Image 2025-01-30 at 22 35 20](https://github.com/user-attachments/assets/0587670a-eec6-4a8c-a560-ca67d5a11510)

Aba para marcar um novo atendimento - Médicos:

![WhatsApp Image 2025-01-30 at 22 35 20](https://github.com/user-attachments/assets/a56def79-2ae8-465f-b83b-a22f337f7cf6)

Aba de atendimentos já programados:

![WhatsApp Image 2025-01-30 at 22 35 53](https://github.com/user-attachments/assets/c29d3fce-39b3-49bd-a9ad-ba78002d4319)

Tela de edição do Cadastro - Médico:

![WhatsApp Image 2025-01-30 at 22 38 24](https://github.com/user-attachments/assets/fca25474-e832-476b-8088-0c6c40a63900)

Tela de Início - Paciente (telas de cadastro e atendimento são semelhantes às do médico):

![WhatsApp Image 2025-01-30 at 22 39 59](https://github.com/user-attachments/assets/29429227-c723-47d2-bb46-f066c05a539a)

Tela de Cadastros Antigos - ADM:

![WhatsApp Image 2025-01-30 at 22 42 09](https://github.com/user-attachments/assets/3129e1f5-f35e-488f-bfd8-0f7dd1f5157d)

Tela de Novo cadastro - ADM:

![WhatsApp Image 2025-01-30 at 22 43 10](https://github.com/user-attachments/assets/9c9340fb-cf60-472f-91e7-bd65355d37cf)

Tela de Material - ADM:

![WhatsApp Image 2025-01-30 at 22 43 51](https://github.com/user-attachments/assets/7060d459-04f3-47f7-87ea-269a76605e8b)


Ao baixar o projeto, siga as etapas abaixo para configurá-lo corretamente:

- Certifique-se de que todos os arquivos do projeto estejam organizados em uma única pasta.
- No Qt, selecione a opção “Abrir Projeto” e navegue até essa pasta.
- Selecione todos os arquivos, exceto o banco de dados, e abra-os.
- Em seguida, abra o arquivo “login.cpp” e configure a conexão com o banco de dados, apontando para o caminho correto no seu computador. Certifique-se de que o caminho seja compatível com a estrutura do seu sistema operacional.
