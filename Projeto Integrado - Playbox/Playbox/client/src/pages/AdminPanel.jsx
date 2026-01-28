import React, { useState, useEffect } from 'react';
import { userService } from '../services/api';
import '../styles/AdminPanel.css';

const AdminPanel = ({ currentUser, onBack }) => {
  const [users, setUsers] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState('');
  const [successMessage, setSuccessMessage] = useState('');
  const [deleteConfirm, setDeleteConfirm] = useState(null);

  useEffect(() => {
    if (currentUser && currentUser.isAdmin) {
      loadUsers();
    } else {
      setError('Acesso negado. Apenas administradores podem acessar esta página.');
      setLoading(false);
    }
  }, [currentUser]);

  /**
   * Carrega a lista de usuários não-admin da API.
   * @async
   * @returns {Promise<void>}
   */
  const loadUsers = async () => {
    try {
      setLoading(true);
      setError('');
      setSuccessMessage('');
      const response = await userService.getAllUsers();
      // Filtrar apenas usuários não-admin
      const nonAdminUsers = response.users.filter(user => !user.isAdmin);
      setUsers(nonAdminUsers);
    } catch (err) {
      setError('Erro ao carregar usuários: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao carregar usuários:', err);
    } finally {
      setLoading(false);
    }
  };

  /**
   * Deleta um usuário pelo ID.
   * @async
   * @param {number} userId ID do usuário
   * @returns {Promise<void>}
   */
  const handleDeleteUser = async (userId) => {
    try {
      setError('');
      setSuccessMessage('');
      await userService.deleteUser(userId);
      const deletedUser = deleteConfirm;
      setUsers(prev => prev.filter(user => user.id !== userId));
      setDeleteConfirm(null);
      setSuccessMessage(`Usuário "${deletedUser.name}" foi deletado com sucesso!`);
      
      // Limpar mensagem de sucesso após 3 segundos
      setTimeout(() => {
        setSuccessMessage('');
      }, 3000);
    } catch (err) {
      setError('Erro ao deletar usuário: ' + (err.response?.data?.error || err.message));
      console.error('Erro ao deletar usuário:', err);
      setDeleteConfirm(null);
    }
  };

  /**
   * Exibe modal de confirmação para deletar usuário.
   * @param {Object} user Usuário a ser deletado
   */
  const confirmDelete = (user) => {
    setDeleteConfirm(user);
  };

  /**
   * Cancela a exclusão do usuário.
   */
  const cancelDelete = () => {
    setDeleteConfirm(null);
  };

  if (!currentUser || !currentUser.isAdmin) {
    return (
      <div className="admin-panel-container">
        <div className="admin-panel-header">
          <button onClick={onBack} className="btn btn-secondary back-button">
            ← Voltar
          </button>
        </div>
        <div className="error-message">
          Acesso negado. Apenas administradores podem acessar esta página.
        </div>
      </div>
    );
  }

  if (loading) {
    return (
      <div className="admin-panel-container">
        <div className="admin-panel-header">
          <button onClick={onBack} className="btn btn-secondary back-button">
            ← Voltar
          </button>
        </div>
        <div className="loading">Carregando usuários...</div>
      </div>
    );
  }

  return (
    <div className="admin-panel-container">
      <div className="admin-panel-header">
        <button onClick={onBack} className="btn btn-secondary back-button">
          ← Voltar
        </button>
        <h1>Painel de Administração</h1>
      </div>

      {error && <div className="error-message">{error}</div>}

      <div className="admin-content">
        {successMessage && (
          <div className="success-message">
            {successMessage}
          </div>
        )}
        
        <div className="users-section">
          <div className="section-header">
            <h2>Usuários Cadastrados</h2>
            <span className="users-count">({users.length} usuários)</span>
          </div>

          {users.length > 0 ? (
            <div className="users-table">
              <div className="table-header">
                <div className="header-cell">Nome</div>
                <div className="header-cell">Email</div>
                <div className="header-cell">Data de Cadastro</div>
                <div className="header-cell">Ações</div>
              </div>
              
              {users.map((user) => (
                <div key={user.id} className="table-row">
                  <div className="table-cell">
                    <div className="user-info">
                      <span className="user-name">{user.name}</span>
                    </div>
                  </div>
                  <div className="table-cell">
                    <span className="user-email">{user.email}</span>
                  </div>
                  <div className="table-cell">
                    <span className="user-date">
                      {new Date(user.createdAt).toLocaleDateString('pt-BR')}
                    </span>
                  </div>
                  <div className="table-cell">
                    <button
                      onClick={() => confirmDelete(user)}
                      className="btn btn-danger btn-small"
                    >
                     Deletar
                    </button>
                  </div>
                </div>
              ))}
            </div>
          ) : (
            <div className="no-users">
              <p>Nenhum usuário não-admin encontrado.</p>
            </div>
          )}
        </div>
      </div>

      {/* Modal de confirmação de exclusão */}
      {deleteConfirm && (
        <div className="delete-modal-overlay">
          <div className="delete-modal">
            <div className="delete-modal-header">
              <h3>Confirmar Exclusão</h3>
            </div>
            <div className="delete-modal-content">
              <p>Tem certeza que deseja deletar o usuário:</p>
              <div className="user-to-delete">
                <strong>{deleteConfirm.name}</strong>
                <br />
                <span>{deleteConfirm.email}</span>
              </div>
              <p className="warning-text">Esta ação não pode ser desfeita!</p>
            </div>
            <div className="delete-modal-actions">
              <button
                onClick={cancelDelete}
                className="btn btn-secondary"
              >
                Cancelar
              </button>
              <button
                onClick={() => handleDeleteUser(deleteConfirm.id)}
                className="btn btn-danger"
              >
                Confirmar Exclusão
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
};

export default AdminPanel;
