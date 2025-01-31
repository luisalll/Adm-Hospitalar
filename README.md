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
![WhatsApp Image 2025-01-30 at 22 31 30 (1)](https://github.com/user-attachments/assets/58456626-7980-4181-a30f-1743539fef70)

Tela de login:
![WhatsApp Image 2025-01-30 at 22 34 22](https://github.com/user-attachments/assets/2ac3889a-0ae3-4ba5-b731-17f989a6e298)

Tela de Início - Médico:
![WhatsApp Image 2025-01-30 at 22 35 20](https://github.com/user-attachments/assets/416af405-3714-45d4-8659-bbff5bd78d3f)

Aba para marcar um novo atendimento - Médicos:
![WhatsApp Image 2025-01-30 at 22 35 53](https://github.com/user-attachments/assets/13f1a7f5-1810-4120-98d6-a9d11ac3c54b)

Aba de atendimentos já programados:
![WhatsApp Image 2025-01-30 at 22 36 11](https://github.com/user-attachments/assets/7c976091-ac07-4f60-9ecb-d2abe4f78ec4)

Tela de edição do Cadastro - Médico:
![WhatsApp Image 2025-01-30 at 22 38 24](https://github.com/user-attachments/assets/279979b2-d580-4350-b3e1-e9b0006af304)

Tela de Início - Paciente (telas de cadastro e atendimento são semelhantes às do médico):
![WhatsApp Image 2025-01-30 at 22 39 59](https://github.com/user-attachments/assets/7d34d280-db50-498f-b092-d98a9b7fe15d)

Tela de Cadastros Antigos - ADM:
![WhatsApp Image 2025-01-30 at 22 42 09](https://github.com/user-attachments/assets/ecb99f22-a781-47af-bfba-abeabf1a4296)

Tela de Novo cadastro - ADM:
![WhatsApp Image 2025-01-30 at 22 43 10](https://github.com/user-attachments/assets/e6885ba1-5931-4b03-ae0f-2274f573dffc)

Tela de Material - ADM:
![WhatsApp Image 2025-01-30 at 22 43 51](https://github.com/user-attachments/assets/0bf8a4a7-7d68-42b5-bfb9-3e55de536e5c)


Ao baixar o projeto, siga as etapas abaixo para configurá-lo corretamente:

- Certifique-se de que todos os arquivos do projeto estejam organizados em uma única pasta.
- No Qt, selecione a opção “Abrir Projeto” e navegue até essa pasta.
- Selecione todos os arquivos, exceto o banco de dados, e abra-os.
- Em seguida, abra o arquivo “login.cpp” e configure a conexão com o banco de dados, apontando para o caminho correto no seu computador. Certifique-se de que o caminho seja compatível com a estrutura do seu sistema operacional.
