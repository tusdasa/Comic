package net.tusdasa.comic.model;

import java.io.Serializable;
import java.util.Date;

import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;

@Entity
public class Comic implements Serializable {

    @Id
    private Long comic_id;

    private String comic_name;

    private Date created_at;

    private Date updated_at;

    private String comic_cover;

    private Long point;

    private Integer category_id;

    private String introduction;

    public Comic() {
    }

    public Long getComic_id() {
        return comic_id;
    }

    public void setComic_id(Long comic_id) {
        this.comic_id = comic_id;
    }

    public String getComic_name() {
        return comic_name;
    }

    public void setComic_name(String comic_name) {
        this.comic_name = comic_name;
    }

    public Date getCreated_at() {
        return created_at;
    }

    public void setCreated_at(Date created_at) {
        this.created_at = created_at;
    }

    public Date getUpdated_at() {
        return updated_at;
    }

    public void setUpdated_at(Date updated_at) {
        this.updated_at = updated_at;
    }

    public String getComic_cover() {
        return comic_cover;
    }

    public void setComic_cover(String comic_cover) {
        this.comic_cover = comic_cover;
    }

    public Long getPoint() {
        return point;
    }

    public void setPoint(Long point) {
        this.point = point;
    }

    public Integer getCategory_id() {
        return category_id;
    }

    public void setCategory_id(Integer category_id) {
        this.category_id = category_id;
    }

    public String getIntroduction() {
        return introduction;
    }

    public void setIntroduction(String introduction) {
        this.introduction = introduction;
    }

    @Override
    public String toString() {
        return "Comic{" +
                "comic_id=" + comic_id +
                ", comic_name='" + comic_name + '\'' +
                ", created_at=" + created_at +
                ", updated_at=" + updated_at +
                ", comic_cover='" + comic_cover + '\'' +
                ", point=" + point +
                ", category_id=" + category_id +
                ", introduction='" + introduction + '\'' +
                '}';
    }
}
