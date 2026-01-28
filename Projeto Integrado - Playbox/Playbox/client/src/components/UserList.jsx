import React from 'react';
import '../styles/UserList.css';

const UserList = ({ users, onEdit, onDelete }) => {
  /**
   * Lista de usuários cadastrados.
   * @module UserList
   * @param {Object} props Propriedades do componente
   * @param {Array} props.users Lista de usuários
   * @returns {JSX.Element} Elemento React da lista de usuários
   */
  /**
   * Renderiza mensagem quando não há usuários.
   * @returns {JSX.Element}
   */
  if (users.length === 0) {
    return (
      <div className="user-list-container">
        <h2>Lista de Usuários</h2>
        <p className="no-users">Nenhum usuário encontrado.</p>
      </div>
    );
  }

  return (
    <div className="user-list-container">
      <h2>Lista de Usuários</h2>
      <div className="users-grid">
        {users.map(user => (
          <div key={user.id} className="user-card">
            <div className="user-info">
              <h3>{user.name}</h3>
              <p className="user-email">{user.email}</p>
              <div className="user-details">
                <span className={`user-badge ${user.isAdmin ? 'admin' : 'user'}`}>
                  {user.isAdmin ? 'Admin' : 'Usuário'}
                </span>
                <span className="user-date">
                  Criado em: {new Date(user.createdAt).toLocaleDateString('pt-BR')}
                </span>
              </div>
            </div>
            <div className="user-actions">
              <button 
                onClick={() => onEdit(user)}
                className="btn btn-edit"
              >
                Editar
              </button>
              <button 
                onClick={() => onDelete(user.id)}
                className="btn btn-delete"
              >
                Deletar
              </button>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default UserList;
